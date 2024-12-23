//Arduino Motor shield library for esp32
#include <espMotorShield.h>

// Create motor objects
Motor motor1(1);
Motor motor2(2);
Motor motor3(3);
Motor motor4(4);

void setup() {
  Serial.begin(115200);

  // Initialize motor shield
  motor1.init(12, 17, 19, 14); //Latch, Clock, Data, Enable

  // Enable motor shield
  motor1.enableShield();
  Serial.println("Motor shield enabled.");
}

void loop() {
  // Test Motor 1
  motor1.setSpeed(255); // 50% speed
  motor1.run(FORWARD);
  Serial.println("M1 Forward");
  delay(2000);
  motor1.run(RELEASE);

  motor1.run(BACKWARD);
  Serial.println("M1 Backward");
  delay(2000);
  motor1.run(RELEASE);

  // Test Motor 2
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  Serial.println("M2 Forward");
  delay(2000);
  motor2.run(RELEASE);

  motor2.run(BACKWARD);
  Serial.println("M2 Backward");
  delay(2000);
  motor2.run(RELEASE);

  // Test Motor 3
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  Serial.println("M3 Forward");
  delay(2000);
  motor3.run(RELEASE);

  motor3.run(BACKWARD);
  Serial.println("M3 Backward");
  delay(2000);
  motor3.run(RELEASE);

  // Test Motor 4
  motor4.setSpeed(255);
  motor4.run(FORWARD);

  delay(2000);
  motor4.run(RELEASE);
  Serial.println("M4 Forward");
  motor4.run(BACKWARD);
  Serial.println("M4 Backward");
  delay(2000);
  motor4.run(RELEASE);

  delay(5000);
}
