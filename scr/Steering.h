#ifndef STEERING_H
#define STEERING_H

#include <Servo.h>
#include "Config.h"
#include "Sensors.h"

extern Servo steering;
extern RobotState state;

extern int cornerCount;
extern int lapCount;
extern int wallHits;
extern int clearHits;
extern int finishHits;
extern bool finishArmed;
extern unsigned long turnStartTime;

void initSteering();
void normalSteering();
void startCorner();
void completeCorner();

#endif
