#ifndef __CAM_SENSOR_H__
#define __CAM_SENSOR_H__

#include "esp_camera.h"
// #include "esp_err.h"

#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "camera_pins.h"

class CamSensor
{
private:
    sensor_t *sensor;
    camera_config_t cameraConfig;
    static bool sensorInited;
public:
    CamSensor();
    ~CamSensor();
    bool isSensorInited();
    sensor_t *getSensor();
    esp_err_t init();
    esp_err_t deinit();
};

#endif
