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

void mainMenuScreen(int position)
{
    clearDisplay();
    addTitle(MAIN_MENU, ARROW);
    
    switch (position)
    {
    case 0:
        printDotAtTheBeginningOfARow(2);
        printAlignedText("Continious Mode", 2, LEFT, 1);
        printAlignedText("Bypass Mode", 3, LEFT);
        break;
    case 1:
        printDotAtTheBeginningOfARow(3);
        printAlignedText("Continious Mode", 2, LEFT);
        printAlignedText("Bypass Mode", 3, LEFT, 1);
        break;
    case 2:
        printDotAtTheBeginningOfARow(3);
        printAlignedText("Bypass Mode", 2, LEFT);
        printAlignedText("Fine adjust", 3, LEFT, 1);
        break;    
    default:
        break;
    }
}

void bypassModeScreen()
{
    clearDisplay();
    addTitle(BYPASS_MODE, ARROW);

    // Just for testing---------------------
    // for (int i = 0; i < 10; i++)
    // {
    //     addStatusMessage(ENGRAVING, LINE);
    //     delay(1000);
    //     addStatusMessage(PAUSE, LINE);
    //     delay(1000);
    // }
    // -------------------------------------
}