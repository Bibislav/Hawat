#include "config.h"
#include "AccelStepper.h"
#include <Arduino.h>

AccelStepper stepper(AccelStepper::DRIVER, STEPPER_PULL_PIN, STEPPER_DIRECTION_PIN);

void initStepper() {   
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void moveStepper() {
    int steps = stepper.distanceToGo();
    if (steps == 0) {
        int stepsForOneEighth = STEPS_FOR_CIRCLE / 8;
        stepper.move(stepsForOneEighth);
    }
}