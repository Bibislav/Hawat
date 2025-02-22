#include "screen.h"
#include "config.h"
#include "display.h"

void welcomeScreen(float sleepSeconds) {
    clearDisplay();
    createBorder();
    printAlignedText("-Hawat-", 1, CENTER);
    printAlignedText(VERSION, 2, CENTER);
    // TODO: Make this with delayless delay
    delay(sleepSeconds * 1000);
}
void welcomeScreen() {
    welcomeScreen(2.5);
}

void mainMenuScreen() {
    addTitle(MAIN_MENU, ARROW);
}