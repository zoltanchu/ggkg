#ifndef __GIMBAL_H__
#define __GIMBAL_H__
#include <ESP32Servo.h>

#define SERVO_PITCH 14
#define SERVO_YAW 15
#define SERVO_POWER_TIME_MAX    3

#define SERVO_ANGLE_TO_MS(a) a * 100 / 9 + 500

// #ifdef PWM_BASE_INDEX
// #undef PWM_BASE_INDEX
// #define PWM_BASE_INDEX 2
// #endif
// ESP32PWM.cpp, pwmChannel = 2

class Gimbal
{
private:
    // (10/10/2023 kontornl) reserve 2 channel for camera sensor, the servos must be inited in this turn
    static Servo servoReserved0, servoReserved1, servoPitch, servoYaw;
    static time_t tsPitchLastOpened, tsYawLastOpened;
    static bool silentTaskDonePitch, silentTaskDoneYaw;
    static int currPitchMs, currYawMs;
    int targetPitchMs, targetYawMs, silentIntervMs;
public:
    Gimbal(/* args */);
    ~Gimbal();
    void init();
    int getPitchAngle();
    int getYawAngle();
    void setPitchAngle(int angle);
    void setYawAngle(int angle);
    void setPitchMs(int ms);
    void setYawMs(int ms);
    void setTargetPitchAngle(int angle);
    void setTargetYawAngle(int angle);
    void setSilentIntervalMs(int interval);
    bool reqSleepPitch(bool force=false);
    bool reqSleepYaw(bool force=false);
    void handleSilentTask();
};

#endif
