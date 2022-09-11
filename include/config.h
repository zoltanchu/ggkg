#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "Arduino.h"

extern int pitch_default;
extern int yaw_default;
extern const char *hostname;
extern const char *ssid;
extern const char *password;
//extern IPAddress local_ip;
//extern IPAddress netmask;
//extern IPAddress gateway;
extern IPAddress wg_local_ip;
extern const char *wg_private_key;
extern const char *wg_endpoint_address;
extern const char *wg_public_key;
extern uint16_t wg_endpoint_port;


#endif
