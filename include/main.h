#ifndef __MAIN_H__
#define __MAIN_H__

// #define CORE_DEBUG_LEVEL ARDUHAL_LOG_LEVEL_DEBUG

#include <Arduino.h>
#include "esp_camera.h"
#include <ESP32Servo.h>
#define CAMERA_MODEL_AI_THINKER // Has PSRAM

#define WLAN_CONN_TIME_MAX  10e3
#define CAM_IDLE_TIME_MAX   30

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
extern Servo s_pitch;
extern Servo s_yaw;
extern time_t ts, ts_camera_open;
extern char hostmsg[];
extern char *hostamsg;

void net_asm();
esp_err_t cam_init();
esp_err_t cam_deinit();
esp_err_t cam_reinit();
void startCameraServer();

#endif
