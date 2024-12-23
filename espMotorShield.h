// This library is for Arduino motor Shield V1 
// For ESP32 Based wemos d1 32 an arduino shaped variant only works with Motor not stepper support yet

#ifndef MOTORSHIELD_H
#define MOTORSHIELD_H

#include <Arduino.h>

enum MotorDirection {
    FORWARD,
    BACKWARD,
    RELEASE
};

class Motor {
public:
    Motor(uint8_t id);

    // Initialization and shield control
    static void init(uint8_t serial, uint8_t clock, uint8_t latch, uint8_t enable);
    void enableShield();
    void disableShield();

    // Motor control
    void setSpeed(uint8_t speed);
    void run(MotorDirection direction);

private:
    uint8_t motorId;
    uint8_t pwmPin;
    uint8_t pwmChannel;
    uint8_t leftBitMask;
    uint8_t rightBitMask;

    // Static shared variables
    static uint8_t serialPin, clockPin, latchPin, enablePin;
    static uint8_t motorControl;
    static const uint8_t motorBitMap[4][2];

    // Internal functions
    void updateMotors();
};

#endif
