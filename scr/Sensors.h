#ifndef SENSORS_H
#define SENSORS_H

#include "Config.h"

// Global distance variables
extern float startDistance;
extern float frontDistance;
extern float rightDistance;
extern float leftDistance;

// Sensor function declarations
void initSensors();
float readDistance(int trig, int echo);
void readAllSensors();
float saveStartDistance();

#endif
