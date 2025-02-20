#include "screen.h"
#include "config.h"
#include "display.h"

void welcomeScreen(float sleepSeconds) {
    clearDisplay();
    createBorder();
    printAlignedText("-Hawat-", 2, CENTER);
    printAlignedText(VERSION, 3, CENTER);
    // TODO: Make this with delayless delay
    delay(sleepSeconds * 1000);
}
void welcomeScreen() {
    welcomeScreen(2.5);
}

void mainMenuScreen() {
    addTitle(MAIN_MENU, ARROW);
}