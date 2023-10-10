#include "main.h"
#include "base64.h"
#include "time.h"
#include "esp_sntp.h"
#include <WiFi.h>

// #include "sdkconfig.h"
#include "persist.h"
#if CONFIG_HTTPD_MAX_REQ_HDR_LEN <= 512
#error "CONFIG_HTTPD_MAX_REQ_HDR_LEN is not configured."
#endif
#include "CamSensor.h"
// #include "soc/rtc.h"

#define TAG "main"

const char *ntp_server1 = "pool.ntp.org";
const char *ntp_server2 = "time.nist.gov";
const char *ntp_server3 = "cn.ntp.org.cn";
// const char *timezone = "HKT-8";
const long gmtOffset_sec = 8 * 60 * 60;
const int daylightOffset_sec = 0;

bool isStreaming = false;
uint8_t flash_br = 0;
String httpd_auth_b64;
String uart0_rbuf = "";

HardwareSerial uart0 = Serial;
Gimbal gimbal;

#if SET_WIREGUARD_ENABLE
#include <WireGuard-ESP32.h>

WireGuard wg;
#endif

char hostmsg[256];
char *hostamsg = hostmsg;

int retry_wifi = 0;

void setup() {
    // esp_log_level_set("*", ESP_LOG_DEBUG);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_FLASH, OUTPUT);

    digitalWrite(LED_BUILTIN, LOW);

    strcpy(hostmsg, hostname);
    hostamsg = hostmsg + strlen(hostmsg);

    uart0.begin(115200);
    Serial.setDebugOutput(true);
    uart0.println();

    // uart0.print("Initializing persistence: ");
    // persist_init();
    // uart0.println("done.");
    // ESP_LOGI(TAG,);
    uart0.print("setup: init Gimbal: ");
    gimbal.init();
    uart0.println("done.");
    analogWrite(LED_FLASH, 1);

    uart0.print("setup: cam init: ");
    CamSensor camSensor;
    esp_err_t err = camSensor.init();
    if(err == ESP_OK) uart0.println("done.");
    else {
        uart0.printf("fail 0x%x", err);
        uart0.println("");
        analogWrite(LED_FLASH, 3);
    }

    // comment the line below if you needn't static IP
#if SET_WIFI_USE_STATIC_IP
    WiFi.config(IPAddress(local_ip), IPAddress(gateway), IPAddress(netmask), IPAddress(223, 5, 5, 5), IPAddress(gateway));
#endif
    WiFi.setAutoConnect(true);
    //WiFi.setAutoReconnect(true);
    //WiFi.persistent(true);
    WiFi.setSleep(true);
    WiFi.setHostname(hostname);
    // TODO: Implement permanent config over serial or hotspot
#ifdef WLAN_UART_CONFIGURABLE
    while(uart0.available()) uart0.print(uart0.read());
    uart0.println("Press any key to interrupt WLAN default config (1s).");
    delay(1000);
    if(uart0.available()) {
        unsigned char _ssid[64] = "", _pass[64] = "";
        while(uart0.available()) uart0.print(uart0.read());
        uart0.print("SSID: ");
        while(_ssid[0] == '\0') {
            while(uart0.available()) {
                char in = uart0.read(); uart0.print(in);
                if(in=='\r' || in=='\n') {
                    uart0_rbuf.getBytes(_ssid, uart0_rbuf.length());
                    uart0_rbuf.clear();
                    break;
                }
                else uart0_rbuf += in;
            }
        }
        while(uart0.available()) uart0.print(uart0.read());
        uart0.print("Password: ");
        while(_pass[0] == '\0') {
            while(uart0.available()) {
                char in = uart0.read(); uart0.print('*');
                if(in=='\r' || in=='\n') {
                    uart0_rbuf.getBytes(_pass, uart0_rbuf.length());
                    uart0_rbuf.clear();
                    break;
                }
                else uart0_rbuf += in;
            }
        }
        while(uart0.available()) uart0.print(uart0.read());
        uart0.print("Connecting to wlreless LAN ");
        uart0.print((char *) _ssid);
        uart0.print(": ");
        WiFi.begin((const char *) _ssid, (const char *) _pass);
    } else {
#endif
        uart0.print("setup: WLAN conn: ");
        uart0.print(ssid);
        uart0.print(": ");
        // TODO: online config over serial, bluetooth
        WiFi.begin(ssid, password);
#ifdef WLAN_UART_CONFIGURABLE
    }
#endif
    analogWrite(LED_FLASH, 0);
    if(WiFi.waitForConnectResult() != WL_CONNECTED) {
        while(!WiFi.isConnected()) {
            uart0.print(".");
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            WiFi.begin(ssid, password);
        }
    }
    uart0.println("done");

#if SET_WIREGUARD_ENABLE
    uart0.print("Start sync time: ");
    configTime(gmtOffset_sec, daylightOffset_sec, ntp_server1, ntp_server2, ntp_server3);
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED) {
        uart0.println("SNTP is not completed.");
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
    }
    if (! getLocalTime(&struct_ts))
        uart0.println("Fail to get local time.");
    uart0.print("SNTP sync done: ");
    uart0.println(&struct_ts, "%B %d %Y %H:%M:%S");
#endif

    retry_wifi = 10;

    if(strlen(httpd_auth)) {
        httpd_auth_b64 = base64::encode(httpd_auth);
        uart0.print("setup: http basic auth ");
        uart0.print(httpd_auth);
        uart0.print(" (");
        uart0.print(httpd_auth_b64);
        uart0.println(").");
    }
    uart0.print("setup: http server: ");
    startCameraServer();
    uart0.print("http://");
    uart0.print(WiFi.localIP());
    uart0.println(".");
    // esp_sleep_enable_timer_wakeup(100e3);

    digitalWrite(LED_BUILTIN, HIGH);
    analogWrite(LED_FLASH, flash_br);
}

void loop() {
    /* Auto sleep after 30s idle
    if(!isStreaming) {
        if(ts - ts_camera_open > CAM_IDLE_TIME_MAX) {
            esp_light_sleep_start();
        }
    }
    */
    /* Auto close camera after 30s idle
    if(camera_is_inited && !isStreaming) {
        time(&ts);
        if(ts - ts_camera_open > CAM_IDLE_TIME_MAX) {
            if(esp_camera_deinit() == ESP_OK) camera_is_inited = false;
        }
    }
    delay(500);
    */
    gimbal.handleSilentTask();
    // release servos to save energy
    if(gimbal.reqSleepPitch())
        uart0.println("loop: pitch slept");
    if(gimbal.reqSleepYaw())
        uart0.println("loop: yaw slept");

    if (WiFi.isConnected() && retry_wifi) {
        uart0.println("loop: WLAN conn done");
#if SET_WIREGUARD_ENABLE
        if (! wg.is_initialized()) {
            //uart0.print("Stop old wg connection: ");
            //wg.end();
            //uart0.println("done.");
            // do not need to restart?
            uart0.print("Start wg: ");
            if (wg.begin(
                wg_local_ip,           // IP address of the local interface
                wg_private_key,        // Private key of the local interface
                wg_endpoint_address,   // Address of the endpoint peer.
                wg_public_key,         // Public key of the endpoint peer.
                wg_endpoint_port))     // Port pf the endpoint peer.
                uart0.println("done.");
            else
                uart0.println("initialize failed.");
        }
#endif
        retry_wifi = 0;
        // startCameraServer();
    }
    if (!WiFi.isConnected() && ! retry_wifi) {
        uart0.println("loop: WLAN disconn retry timed out");
        // stopCameraServer();
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        retry_wifi = 60;
    }
    if (!WiFi.isConnected() || retry_wifi) {
        uart0.printf("loop: WLAN stat 0x%x", WiFi.status());
        uart0.println();
        digitalWrite(LED_BUILTIN, LOW); delay(500);
        digitalWrite(LED_BUILTIN, HIGH); delay(500);
        if (retry_wifi > 0) retry_wifi--;
    // } else {
    //     delay(10000);
    }
}
