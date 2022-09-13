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

GGKG ask for a dynamic IP address in default. For a static IP address, set `#define SET_WIFI_USE_STATIC_IP 1` in `config.h`, then set `local_ip` as the static IP address, `netmask` and `gateway` as what you wish.

GGKG also support [wireguard](https://www.wireguard.com/). To enable it, set `#define SET_WIREGUARD_ENABLE   1` in `config.h`, then set `wg_local_ip` for wireguard interface address(netmask will be 255.255.255.255), `wg_private_key` for interface private key, `wg_endpoint_address` for endpoint address or domain, `wg_endpoint_port` for endpoint port, and `wg_public_key` for endpoint public key.

## HTTP Web Server ##

GGKG provides web page at **root** of its web server. In `Settings Panel`, `Peripherals` submenu is for servos and Flashlight LED, and the other submenu contains items in **CameraWebServer**.

This gimbal project may be useful and can't be simpler. It's for our enjoyment.

## Unstable of Wireguard Connection ##

In some cases, say wifi reconnected after a period of connection lost, wireguard could be unable to reconnect. We found that the program would tring to send initralization requests continously but failed to receive any server response, and believe it is NAT network to be claim.

In general wireguard client, we set `PersistentKeepalive` to avoid such situation, quote [WireGuard Quick Start Manual](https://www.wireguard.com/quickstart/#nat-and-firewall-traversal-persistence) here:

>But if you're behind NAT or a firewall and you want to receive incoming connections long after network traffic has gone silent, this option will keep the "connection" open in the eyes of NAT.

For more information, refer to [this log](test/ggkg_wg_debug.md).
