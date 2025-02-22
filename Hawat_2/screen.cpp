#include "screen.h"
#include "config.h"
#include "display.h"
#include <Arduino.h> // Just for testing

void welcomeScreen(float sleepSeconds) {
    clearDisplay();
    createBorder();
    printAlignedText("-Hawat-", 1, CENTER);
    printAlignedText(VERSION, 2, CENTER);
    // TODO: Make this with delayless delay
    delay(sleepSeconds * 1000);
    clearDisplay();
}
void welcomeScreen() {
    welcomeScreen(2.5);
}

void mainMenuScreen() {
    addTitle(MAIN_MENU, ARROW);
}

void bypassMode() {
    clearDisplay();
    addTitle(BYPASS_MODE, ARROW);

    // Just for testing---------------------
    for (int i = 0; i < 10; i++)
    {
        addStatusMessage(ENGRAVING, LINE);
        delay(1000);
        addStatusMessage(PAUSE, LINE);
        delay(1000);
    }
    // -------------------------------------
}