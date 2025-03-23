#include <Arduino.h>
#include "config.h"

void initRotaryEncoder() {
    pinMode(ROTARY_ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ROTARY_ENCODER_PIN_B, INPUT_PULLUP);
}