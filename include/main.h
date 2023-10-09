#ifndef __MAIN_H__
#define __MAIN_H__

// #define CORE_DEBUG_LEVEL ARDUHAL_LOG_LEVEL_DEBUG

#include <Arduino.h>
#include "esp_camera.h"
#include "esp_http_server.h"
#include "nvs_flash.h"
#include <ESP32Servo.h>
#include "config.h"
#define CAMERA_MODEL_AI_THINKER // Has PSRAM

#define SERVO_POWER_TIME_MAX    3
#define WLAN_CONN_TIME_MAX      10e3
#define CAM_IDLE_TIME_MAX       30

#define LED_FLASH 4
#define LED_BUILTIN 33
#define SERVO_PITCH 14
#define SERVO_YAW 15
// #ifdef PWM_BASE_INDEX
// #undef PWM_BASE_INDEX
// #define PWM_BASE_INDEX 2
// #endif
// ESP32PWM.cpp, pwmChannel = 2

extern bool camera_is_inited, isStreaming;
extern uint8_t flash_br;
extern camera_config_t config;
extern HardwareSerial uart0;
extern Servo s_pitch, s_yaw;
extern time_t ts, ts_camera_open, ts_yaw, ts_pitch;
extern String httpd_auth_b64;
extern char hostmsg[];
extern char *hostamsg;
extern int intrv_ms;
extern int curr_pitch, curr_yaw, dest_pitch, dest_yaw;
extern bool done_pitch, done_yaw;

void net_asm();
esp_err_t cam_init();
esp_err_t cam_deinit();
esp_err_t cam_reinit();
void startCameraServer();
esp_err_t stopCameraServer();

#endif
