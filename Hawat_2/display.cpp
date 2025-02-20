#include "display.h"
#include "config.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// ==== Basic functionality ====
void initDisplay() {
    lcd.begin(LCD_COLUMNS, LCD_ROWS);
    lcd.clear();
}

void clearDisplay() {
    lcd.clear();
}

void setCursorAtOrigin() {
    lcd.setCursor(0,0);
}

bool checkBoundary(int x, int y) {
    return (x >= 0 && x < LCD_COLUMNS) && (y >= 0 && y < LCD_ROWS);
}

void setCursorAtTheSpecificPosition(int x, int y) {
    if (!checkBoundary(x,y)) {
        // TODO: Add some kind  of debug or log!
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

void clearRow(int row) {
    fillRowWith(' ', row);
}

void clearColumn(int column) {
    fillColumnWith(' ', column);
}

void printLineToRow(String s, int row) {
    setCursorAtTheBeginningOfARow(row);
    lcd.print(s);
}

// ==== Specific scenarions ====
void createBorder() {
    createBorder('X');
}
void createBorder(char decorationPattern) {
    fillRowWith(decorationPattern, 0);
    fillRowWith(decorationPattern, LCD_ROWS-1);
    fillColumnWith(decorationPattern, 0);
    fillColumnWith(decorationPattern, LCD_COLUMNS-1);
}

// ==== Screen ====

void welcomeScreen() {
    welcomeScreen(2.5);
} 
void welcomeScreen(float sleepSeconds) {
    clearDisplay();
    createBorder();
    printAlignedText("-Hawat-", 2, CENTER);
    printAlignedText(VERSION, 3, CENTER);
    // TODO: Make this with delayless delay
    delay(sleepSeconds * 1000);
}

void printAlignedText(const String &s, int row, PossibleAlign selectedAlign) {
    int lenOfString = s.length(); 
    int position = 0;

    if (lenOfString > LCD_COLUMNS) {
        // TODO: Add some kind  of debug or log!
        return;
    }
    
    switch (selectedAlign) {
        case CENTER:
            position = (LCD_COLUMNS / 2) - (lenOfString / 2) - 1;  
            break;

        case LEFT:
            position = 0;
            break;

        case RIGHT:
            position = LCD_COLUMNS - lenOfString - 1; 
            break;
    
        default:
            // TODO: Add some kind  of debug or log!
            break;
    }
    setCursorAtTheSpecificPosition(position, row);
    lcd.print(s);
}

void addTitle(Title title, DecorationPattern decorationPattern) {
    printLineToRow(generateDecorationPattern(decorationPattern), 0);
    printAlignedText(titleToString(title), 0, CENTER);
}

String generateDecorationPattern(DecorationPattern d) {
    switch (d) {
        case ARROW:
            String decorationPatternString;
            for (int i = 0; i < LCD_COLUMNS/2; i++) decorationPatternString += ">";
            for (int i = 0; i < LCD_COLUMNS/2; i++) decorationPatternString += "<";
            return decorationPatternString;
            
        default: 
            // TODO: Add some kind  of debug or log!
            return "er30";
    }
}

String titleToString(Title t) {
    switch (t) {
        case BYPASS_MODE:    return "BYPASS MODE";
        case CONTINIUS_MODE: return "CONTINIUS MODE";
        case MAIN_MENU:      return "MAIN MENU";
        // TODO: Add some kind  of debug or log!
        default:             return "er45";
    }
}