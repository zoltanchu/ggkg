#include "main.h"

nvs_handle nvs_ggkg_handle;
/*
*/
void persist_init() {
    uint8_t _magic;
    size_t __len;
    if(nvs_flash_init() || nvs_open("ggkg", NVS_READWRITE, &nvs_ggkg_handle)
    || nvs_get_u8(nvs_ggkg_handle, "magic", &_magic) || nvs_magic != _magic) {
        nvs_flash_deinit();
        nvs_flash_erase();
        nvs_flash_init();
        nvs_set_u8(nvs_ggkg_handle, "magic", nvs_magic);
        nvs_set_u8(nvs_ggkg_handle, "pitch_def", pitch_default);
        nvs_set_u8(nvs_ggkg_handle, "yaw_def", yaw_default);
        nvs_set_str(nvs_ggkg_handle, "hostname", hostname);
        nvs_set_str(nvs_ggkg_handle, "htauth", httpd_auth);
        nvs_set_str(nvs_ggkg_handle, "panelpath", panel_path);
        nvs_set_str(nvs_ggkg_handle, "ssid", ssid);
        nvs_set_str(nvs_ggkg_handle, "passwd", password);
        nvs_set_u32(nvs_ggkg_handle, "localip", (uint32_t) local_ip);
        nvs_set_u32(nvs_ggkg_handle, "nmask", (uint32_t) netmask);
        nvs_set_u32(nvs_ggkg_handle, "gatew", (uint32_t) gateway);
        nvs_commit(nvs_ggkg_handle);
        // nvs_close(nvs_ggkg_handle);
    } else {
        nvs_get_u8(nvs_ggkg_handle, "pitch_def", (uint8_t *) &pitch_default);
        nvs_get_u8(nvs_ggkg_handle, "yaw_def", (uint8_t *) &yaw_default);
        nvs_get_str(nvs_ggkg_handle, "hostname", hostname, &__len);
        nvs_get_str(nvs_ggkg_handle, "htauth", httpd_auth, &__len);
        nvs_get_str(nvs_ggkg_handle, "panelpath", panel_path, &__len);
        nvs_get_str(nvs_ggkg_handle, "ssid", ssid, &__len);
        nvs_get_str(nvs_ggkg_handle, "passwd", password, &__len);
        nvs_get_u32(nvs_ggkg_handle, "localip", (uint32_t *) &local_ip[0]);
        nvs_get_u32(nvs_ggkg_handle, "nmask", (uint32_t *) &netmask[0]);
        nvs_get_u32(nvs_ggkg_handle, "gatew", (uint32_t *) &gateway[0]);
        // nvs_close(nvs_ggkg_handle);
    }
}
