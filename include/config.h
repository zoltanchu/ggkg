#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "Arduino.h"

#define SET_WIFI_USE_STATIC_IP  1
#define SET_WIREGUARD_ENABLE    0
#define SERVO_SILENT_ENABLED    1

extern uint8_t nvs_magic;
extern int pitch_default, yaw_default;
extern char hostname[33], httpd_auth[65], panel_path[17];
extern char ssid[33], password[49];

#if SET_WIFI_USE_STATIC_IP
extern uint8_t local_ip[4], netmask[4], gateway[4];
#endif

#if SET_WIREGUARD_ENABLE
extern IPAddress wg_local_ip;
extern const char *wg_private_key;
extern const char *wg_endpoint_address;
extern const char *wg_public_key;
extern uint16_t wg_endpoint_port;
#endif


#endif
