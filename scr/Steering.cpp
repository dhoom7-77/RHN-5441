#include "Steering.h"

Servo steering;
RobotState state = DRIVE;

int cornerCount = 0;
int lapCount = 0;
int wallHits = 0;
int clearHits = 0;
int finishHits = 0;
bool finishArmed = false;
unsigned long turnStartTime = 0;

void initSteering() {
  steering.attach(SERVO_PIN);
  steering.write(CENTER);
}

void normalSteering() {
  // LEFT WALL TOO CLOSE
  if (leftDistance > 0 && leftDistance < SIDE_DISTANCE) {
    steering.write(SMALL_RIGHT);
    return;
  }

  // RIGHT WALL TOO CLOSE
  if (rightDistance > 0 && rightDistance < SIDE_DISTANCE) {
    steering.write(SMALL_LEFT);
    return;
  }

  // BALANCE BETWEEN WALLS
  if (leftDistance > 0 && rightDistance > 0) {
    float difference = leftDistance - rightDistance;

    // TOO CLOSE TO LEFT
    if (difference < -5) {
      steering.write(SMALL_RIGHT);
    }
    // TOO CLOSE TO RIGHT
    else if (difference > 5) {
      steering.write(SMALL_LEFT);
    }
    // CENTERED
    else {
      steering.write(CENTER);
    }
    return;
  }

  // STRAIGHT
  steering.write(CENTER);
}

void startCorner() {
  Serial.println("START CORNER");
  turnStartTime = millis();
  state = TURNING;

  if (TRACK_TURN_RIGHT) {
    steering.write(RIGHT);
  } else {
    steering.write(LEFT);
  }
}

void completeCorner() {
  steering.write(CENTER);

  cornerCount++;
  lapCount = cornerCount / CORNERS_PER_LAP;

  Serial.print("CORNERS: ");
  Serial.println(cornerCount);

  Serial.print("LAPS: ");
  Serial.println(lapCount);

  wallHits = 0;
  clearHits = 0;

  // THREE LAPS COMPLETED
  if (cornerCount >= TOTAL_CORNERS) {
    state = FINISHING;
    finishArmed = false;
    finishHits = 0;

    Serial.println("THREE LAPS COMPLETED");
    Serial.println("SEARCHING FOR START DISTANCE");
  } else {
    state = CLEARING;
  }
}
