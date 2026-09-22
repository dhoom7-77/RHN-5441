#include "Config.h"
#include "Sensors.h"
#include "Steering.h"

unsigned long lastSensorTime = 0;

void setup() {
  Serial.begin(9600);

  initSensors();
  initSteering();

  Serial.println("ROBOT STARTING");
  delay(2000);

  // SAVE START DISTANCE
  startDistance = saveStartDistance();

  Serial.print("START DISTANCE: ");
  Serial.println(startDistance);

  if (startDistance <= TURN_DISTANCE + 2) {
    Serial.println("INVALID START DISTANCE");
    state = FINISHED;
    steering.write(CENTER);
    return;
  }

  Serial.println("ROBOT READY");
}

void loop() {
  // FINISHED
  if (state == FINISHED) {
    steering.write(CENTER);
    return;
  }

  // TURNING
  if (state == TURNING) {
    if (millis() - turnStartTime >= TURN_TIME) {
      completeCorner();
    }
    return;
  }

  // SENSOR TIMING
  if (millis() - lastSensorTime < 100) {
    return;
  }

  lastSensorTime = millis();
  readAllSensors();

  // DEBUG
  Serial.print("FRONT: ");
  Serial.print(frontDistance);
  Serial.print(" RIGHT: ");
  Serial.print(rightDistance);
  Serial.print(" LEFT: ");
  Serial.print(leftDistance);
  Serial.print(" CORNERS: ");
  Serial.print(cornerCount);
  Serial.print(" LAPS: ");
  Serial.println(lapCount);

  // NORMAL DRIVE
  if (state == DRIVE) {
    if (frontDistance > 0 && frontDistance <= TURN_DISTANCE) {
      wallHits++;
    } else {
      wallHits = 0;
    }

    if (wallHits >= 2) {
      wallHits = 0;
      startCorner();
      return;
    }

    normalSteering();
    return;
  }

  // CLEAR PREVIOUS CORNER
  if (state == CLEARING) {
    normalSteering();

    if (frontDistance >= CLEAR_DISTANCE) {
      clearHits++;
    } else {
      clearHits = 0;
    }

    if (clearHits >= 2) {
      clearHits = 0;
      state = DRIVE;
      Serial.println("NEXT STRAIGHT");
    }

    return;
  }

  // FINISH AFTER THREE LAPS
  if (state == FINISHING) {
    normalSteering();

    if (frontDistance > startDistance + 7.0) {
      finishArmed = true;
    }

    if (finishArmed && frontDistance > 0 && frontDistance <= startDistance + STOP_TOLERANCE) {
      finishHits++;
    } else {
      finishHits = 0;
    }

    if (finishHits >= 2) {
      state = FINISHED;
      steering.write(CENTER);
      Serial.println("THREE LAPS FINISHED!");
      Serial.println("START DISTANCE REACHED!");
    }

    return;
  }
}
