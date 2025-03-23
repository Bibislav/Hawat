#include "screen.h"
#include "config.h"
#include "display.h"
#include <Arduino.h> // Just for testing

void welcomeScreen(float sleepSeconds)
{
    clearDisplay();
    createBorder();
    printAlignedText("-Hawat-", 1, CENTER);
    printAlignedText(VERSION, 2, CENTER);
    // TODO: Make this with delayless delay
    delay(sleepSeconds * 1000);
    clearDisplay();
}
void welcomeScreen()
{
    welcomeScreen(2.5);
}

void mainMenuScreen(unsigned short int position)
{
    clearDisplay();
    addTitle(MAIN_MENU, ARROW);
    
    switch (position)
    {
    case 0:
        printRightArrowAtTheBeginningOfARow(2);
        printAlignedText("Continious Mode", 2, LEFT, 1);
        printAlignedText("Bypass Mode", 3, LEFT, 1);
        printDownArrowAtTheEndOfARow(3);
        break;
    case 1:
        printRightArrowAtTheBeginningOfARow(3);
        printAlignedText("Continious Mode", 2, LEFT, 1);
        printAlignedText("Bypass Mode", 3, LEFT, 1);
        printDownArrowAtTheEndOfARow(3);
        break;
    case 2:
        printRightArrowAtTheBeginningOfARow(3);
        printAlignedText("Bypass Mode", 2, LEFT, 1);
        printAlignedText("Fine adjust", 3, LEFT, 1);
        printUpArrowAtTheEndOfARow(2);
        break;    
    default:
        break;
    }
}

void bypassModeScreen() {
    clearDisplay();
    addTitle(BYPASS_MODE, ARROW);
}

// void bypassModeScreen(Status status)
// {
//     clearDisplay();
//     addTitle(BYPASS_MODE, ARROW);
//     addStatusMessage(status, LINE);
// }