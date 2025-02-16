#include "display.h"
#include "config.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

enum PossibleAlign {
    CENTER,
    LEFT,
    RIGNT
};

// ==== Basic functionality ====
void initDisplay() {
    lcd.begin(LCD_COLUMNS, LCD_ROWS);
    lcd.clear();
}

void clearDisplay() {
    lcd.clear();
}

void clearRow(int row) {
    for (int i = 0; i < LCD_COLUMNS; i++) {
        setCursorAtTheSpecificPosition(i, row);
        lcd.write(' ');
    }
}

void setCursorAtOrigin() {
    lcd.setCursor(0,0);
}

bool checkBoundary(int x, int y) {
    return (x >= 0 && x < LCD_COLUMNS) && (y >= 0 && y < LCD_ROWS);
}

void setCursorAtTheSpecificPosition(int x, int y) {
    if (!checkBoundary(x,y)) {
        // TODO: Dodat neki debug!
        return;
    } 
    lcd.setCursor(x, y);
}

void setCursorAtTheBeginningOfARow(int y) {
    setCursorAtTheSpecificPosition(0, y);
}

void setCursorAtTheEndOfARow(int y) {
    setCursorAtTheSpecificPosition(LCD_COLUMNS-1, y);
}

void fillRowWith(char c, int row) {
    for (int i = 0; i < LCD_COLUMNS; i++) {
        setCursorAtTheSpecificPosition(i, row);
        lcd.write(c);
    }
}

void fillColumnWith(char c, int column) {
    for (int i = 0; i < LCD_ROWS; i++) {
        setCursorAtTheSpecificPosition(column, i);
        lcd.write(c);
    }
}

// ==== Specific scenarions ====
void createBorder() {
    createBorder('X');
}
void createBorder(char c) {
    fillRowWith(c, 0);
    fillRowWith(c, LCD_ROWS-1);
    fillColumnWith(c, 0);
    fillColumnWith(c, LCD_COLUMNS-1);
}

void printString(String s, int row, PossibleAlign selectedAlign) {
    int lenOfString = s.length(); 
    if (lenOfString > LCD_COLUMNS) {
        // TODO: Dodat neki debug!
        return;
    }
    int position = 0;
    switch (selectedAlign)
    {
    case CENTER:
        int middleOfLcd = 0;
        int halfOfWord = 0;
        halfOfWord = (lenOfString / 2);
        middleOfLcd = (LCD_COLUMNS / 2) - 1;
        position = middleOfLcd - halfOfWord;
        setCursorAtTheSpecificPosition(position, row);
        lcd.print(s);  
        break;

    case LEFT:
        setCursorAtTheBeginningOfARow(row);
        lcd.print(s);
        break;

    case RIGNT:
        position = LCD_COLUMNS - lenOfString - 1; 
        setCursorAtTheSpecificPosition(position, row);
        lcd.print(s);
        break;
    
    default:
        // TODO: Dodat neki debug!
        break;
    }
}

void initialScreen() {
    initialScreen(2.5);
}
void initialScreen(float sleepSeconds) {
    clearDisplay();
    createBorder();
    printString("-Hawat-", 2, CENTER);
    printString(VERSION, 3, CENTER);
    // delay(sleepSeconds * 1000); TODO: Make this with dolayless delay
}