#include "screen.h"
#include "config.h"
#include "display.h" // Delete this if possieble
#include <Arduino.h> // Maybe not needed...

void initSwitch() {
    pinMode(PAUSE_SWITCH_PIN, INPUT);
}

void bypassMode() {
    bypassModeScreen();
    while (1) {
        if (digitalRead(PAUSE_SWITCH_PIN) == HIGH) {
            // printAlignedText("PAUSED", 1, CENTER);
            addStatusMessage(PAUSE, LINE);
        } 
        else {
            // printAlignedText("ENGRAVING", 1, CENTER);
            addStatusMessage(ENGRAVING, LINE);
        }
    }
}

void selectMode(unsigned short int position) {
    switch (position)
    {
    case 0:
        // Continious Mode
        break;
    case 1:
        bypassMode();
        break;
    case 2:
        // Fine adjust
        break;    
    default:
        break;
    }
}

