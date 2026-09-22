#include "Sensors.h"

float startDistance = 0;
float frontDistance = -1;
float rightDistance = -1;
float leftDistance = -1;

void initSensors() {
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);

  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
}

float readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH, 20000);

  if (duration == 0) {
    return -1;
  }

  float distance = duration * 0.0343 / 2.0;

  if (distance < 2 || distance > 340) {
    return -1;
  }

  return distance;
}

void readAllSensors() {
  // FRONT
  frontDistance = readDistance(FRONT_TRIG, FRONT_ECHO);
  delay(25);

  // RIGHT
  rightDistance = readDistance(RIGHT_TRIG, RIGHT_ECHO);
  delay(25);

  // LEFT
  leftDistance = readDistance(LEFT_TRIG, LEFT_ECHO);
}

float saveStartDistance() {
  float total = 0;
  int count = 0;

  for (int i = 0; i < 10; i++) {
    float d = readDistance(FRONT_TRIG, FRONT_ECHO);
    if (d > 0) {
      total += d;
      count++;
    }
    delay(60);
  }

  if (count < 5) {
    return -1;
  }

  return total / count;
}
