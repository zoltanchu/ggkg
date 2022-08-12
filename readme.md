# GG & kontornl Gimbal (GGKG) #

A gimbal camera based on Ai-Thinker ESP32-CAM using Arduino and madhephaestus/ESP32Servo library, modified from an example called CameraWebServer.

## Extra Hardware Connection ##

The following code indicates how to connect two 180-degree servos (for example, SG90) with ESP32-CAM board.

```
#define SERVO_PITCH 14
#define SERVO_YAW 15
```

## Configurations ##

Rename `src/config.cpp.example` to `src/config.cpp`, in this file there are several parameters used by initialization process as following.

`pitch_default` ranges 0 to 180, as the initial angle of pitch servo.

`yaw_default` is similar to `pitch_default`.

`hostname` gives name to this device and will be shown on the title bar of its web page and in pictures saved.

`ssid` is the SSID, also known as the name of one Wi-Fi hotspot that GGKG should connect to, with password given by `password`.

For a static IP address, set `local_ip` as the IP address for GGKG. `netmask` and `gateway` should be set appropriately at the same time. For dynamic IP address, comment out the line in `src/main.cpp` and above 3 parameters will become unused.

```
// comment the line below if you needn't static IP
WiFi.config(local_ip, gateway, netmask, IPAddress(223, 5, 5, 5), gateway);
```

## HTTP Web Server ##

GGKG provides web page at **root** of its web server. In `Settings Panel`, `Peripherals` submenu is for servos and Flashlight LED, and the other submenu contains items in **CameraWebServer**.

This gimbal project may be useful and can't be simpler. It's for our enjoyment.
