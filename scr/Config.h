#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ====================================
// ULTRASONIC SENSOR PINS
// ====================================
const int RIGHT_TRIG = 6;
const int RIGHT_ECHO = 7;

const int FRONT_TRIG = 8;
const int FRONT_ECHO = 9;

const int LEFT_TRIG = 11;
const int LEFT_ECHO = 10;

// ====================================
// SERVO PIN & ANGLES
// ====================================
const int SERVO_PIN = 12;

const int CENTER = 90;
const int RIGHT = 135;
const int LEFT = 45;
const int SMALL_RIGHT = 110;
const int SMALL_LEFT = 70;

// ====================================
// DISTANCE SETTINGS (CM)
// ====================================
const float TURN_DISTANCE = 25.0;
const float SIDE_DISTANCE = 15.0;
const float CLEAR_DISTANCE = 38.0;
const float STOP_TOLERANCE = 2.0;

// ====================================
// LAP & TURN SETTINGS
// ====================================
const int TOTAL_LAPS = 3;
const int CORNERS_PER_LAP = 4;
const int TOTAL_CORNERS = TOTAL_LAPS * CORNERS_PER_LAP;

const unsigned long TURN_TIME = 850;
const bool TRACK_TURN_RIGHT = true;

// ====================================
// ROBOT STATES
// ====================================
enum RobotState {
  DRIVE,
  TURNING,
  CLEARING,
  FINISHING,
  FINISHED
};

#endif
