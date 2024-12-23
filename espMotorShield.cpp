#include "espMotorShield.h"

// Static shared variables
uint8_t Motor::serialPin;
uint8_t Motor::clockPin;
uint8_t Motor::latchPin;
uint8_t Motor::enablePin;
uint8_t Motor::motorControl = 0;

// Motor bit map for CCW and CW
const uint8_t Motor::motorBitMap[4][2] = {
    {0b00000100, 0b00000010}, // Motor 1
    {0b00000010, 0b00001000}, // Motor 2
    {0b01000000, 0b00000001}, // Motor 3
    {0b10000000, 0b00100000}  // Motor 4
};

// Constructor
Motor::Motor(uint8_t id) : motorId(id) {
    // Calculate bit masks and PWM pin/channel
    if (id < 1 || id > 4) return;
    leftBitMask = motorBitMap[id - 1][0];
    rightBitMask = motorBitMap[id - 1][1];

    // Assign PWM pin and channel based on motor ID
    switch (id) {
        case 1: pwmPin = 23; pwmChannel = 0; break;
        case 2: pwmPin = 25; pwmChannel = 1; break;
        case 3: pwmPin = 27; pwmChannel = 2; break;
        case 4: pwmPin = 16; pwmChannel = 3; break;
    }

    // Setup PWM for the motor using the latest API
    ledcAttach(pwmPin, 5000, 8); // Attach with 5 kHz frequency and 8-bit resolution
}

// Initialize motor shield
void Motor::init(uint8_t serial, uint8_t clock, uint8_t latch, uint8_t enable) {
    serialPin = serial;
    clockPin = clock;
    latchPin = latch;
    enablePin = enable;

    pinMode(serialPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(enablePin, OUTPUT);

    digitalWrite(enablePin, LOW); // Enable motors by default
}

// Enable the shield
void Motor::enableShield() {
    digitalWrite(enablePin, LOW);
}

// Disable the shield
void Motor::disableShield() {
    digitalWrite(enablePin, HIGH);
}

// Set motor speed
void Motor::setSpeed(uint8_t speed) {
    ledcWrite(pwmPin, speed);
}

// Run motor in a specified direction
void Motor::run(MotorDirection direction) {
    // Clear the current motor control bits
    motorControl &= ~(this->leftBitMask | this->rightBitMask);

    // Apply direction
    if (direction == FORWARD) {
        motorControl |= this->rightBitMask;
        // Serial.print("Motor running: ");
        // Serial.print(motorId);
        // Serial.print(", Direction: FORWARD, Control Bits: ");
        // Serial.println(motorControl, BIN);
    } else if (direction == BACKWARD) {
        motorControl |= this->leftBitMask;
        // Serial.print("Motor running: ");
        // Serial.print(motorId);
        // Serial.print(", Direction: BACKWARD, Control Bits: ");
        // Serial.println(motorControl, BIN);
    } 
    // else {
    //     Serial.print("Motor running: ");
    //     Serial.print(motorId);
    //     Serial.println(", Direction: RELEASE");
    // }

    // Update shift register
    updateMotors();
}

// Update the shift register
void Motor::updateMotors() {
    digitalWrite(latchPin, LOW);
    for (int i = 7; i >= 0; --i) {
        digitalWrite(clockPin, LOW);
        digitalWrite(serialPin, motorControl & (1 << i));
        digitalWrite(clockPin, HIGH);
    }
    digitalWrite(latchPin, HIGH);

    // // Debugging: Print motor control bits
    // Serial.print("Updated MotorControl: ");
    // Serial.println(motorControl, BIN);
}
