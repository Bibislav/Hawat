#include "display.h"
#include "config.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

uint8_t downArrow[] = {
        0b00000,
        0b00000,
        0b00000,
        0b00100,
        0b00100,
        0b10101,
        0b01110,
        0b00100
    };
uint8_t upArrow[] = {
        0b00100,
        0b01110,
        0b10101,
        0b00100,
        0b00100,
        0b00000,
        0b00000,
        0b00000,
    };
uint8_t rightArrow[] = {
        0b00000,
        0b00100,
        0b00010,
        0b11111,
        0b00010,
        0b00100,
        0b00000,
        0b00000
    };    
uint8_t dot[] = {
        0b00000,
        0b00100,
        0b01110,
        0b11111,
        0b01110,
        0b00100,
        0b00000,
        0b00000
    };    

// ==== Basic functionality ====
void initDisplay() {
    lcd.begin(LCD_COLUMNS, LCD_ROWS);
    createChars();
    clearDisplay();
}

void createChars() {
    lcd.createChar(0, dot);
    lcd.createChar(1, downArrow);
    lcd.createChar(2, rightArrow);
    lcd.createChar(3, upArrow);
}

void printUpArrowAtPosition(int x, int y) {
    setCursorAtTheSpecificPosition(x, y);
    lcd.write(byte(3));
}

void printUpArrowAtTheEndOfARow(int y) {
    printUpArrowAtPosition(LCD_COLUMNS-1, y);
}

void printDownArrowAtPosition(int x, int y) {
    setCursorAtTheSpecificPosition(x, y);
    lcd.write(byte(1));
}

void printDownArrowAtTheEndOfARow(int y) {
    printDownArrowAtPosition(LCD_COLUMNS-1, y);
}

void printRightArrowAtPosition(int x, int y) {
    setCursorAtTheSpecificPosition(x, y);
    lcd.write(byte(2));
}

void printRightArrowAtTheBeginningOfARow(int y) {
    printRightArrowAtPosition(0, y);
}

void printDotAtPosition(int x, int y) {
    setCursorAtTheSpecificPosition(x, y);
    lcd.write(byte(0));
}

void printDotAtTheBeginningOfARow(int y) {
    printDotAtPosition(0, y);
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
void createBorder(char decorationPattern) {
    fillRowWith(decorationPattern, 0);
    fillRowWith(decorationPattern, LCD_ROWS-1);
    fillColumnWith(decorationPattern, 0);
    fillColumnWith(decorationPattern, 1);
    fillColumnWith(decorationPattern, LCD_COLUMNS-1);
    fillColumnWith(decorationPattern, LCD_COLUMNS-2);
}
void createBorder() {
    createBorder('X');
}

void printAlignedText(const String &s, int row, PossibleAlign selectedAlign) {
    printAlignedText(s, row, selectedAlign, 0);
}
void printAlignedText(const String &s, int row, PossibleAlign selectedAlign, int offset) {
    int lenOfString = s.length(); 
    int position = 0;

    if ((lenOfString > LCD_COLUMNS) && (lenOfString + abs(offset) > LCD_COLUMNS)) {
        // TODO: Add some kind  of debug or log!
        printDotAtPosition(19,3);
        return;
    }
    
    switch (selectedAlign) {
        case CENTER:
            position = (LCD_COLUMNS / 2) - (lenOfString / 2) + offset;  
            break;

        case LEFT:
            position = 0 + abs(offset);
            break;

        case RIGHT:  
            position = LCD_COLUMNS - lenOfString -  abs(offset); 
            break;
    
        default:
            // TODO: Add some kind  of debug or log!
            break;
    }
    if ((position < 0) || (position + lenOfString > LCD_COLUMNS)) {
        // TODO: Add some kind  of debug or log!
        clearDisplay();
        printDotAtPosition(0,0);
        return;
        }
    setCursorAtTheSpecificPosition(position, row);
    lcd.print(s);
}

void addTitle(Title title, DecorationPattern decorationPattern) {
    printLineToRow(generateDecorationPattern(decorationPattern), 0);
    printAlignedText(titleToString(title), 0, CENTER);
}

void addStatusMessage(Status status, DecorationPattern decorationPattern) {
    printLineToRow(generateDecorationPattern(decorationPattern), 2);
    printAlignedText(statusToString(status), 2, CENTER);
}

// ==== Generate shiit ====
String generateDecorationPattern(DecorationPattern d) {
    String decorationPatternString;
    switch (d) {
        case ARROW:
            for (int i = 0; i < LCD_COLUMNS/2; i++) decorationPatternString += ">";
            for (int i = 0; i < LCD_COLUMNS/2; i++) decorationPatternString += "<";
            break;
        case STAR:
            for (int i = 0; i < LCD_COLUMNS; i++) decorationPatternString += "*";
            break;

        case LINE:
            for (int i = 0; i < LCD_COLUMNS; i++) decorationPatternString += "-";
            break;
            
        default: 
            // TODO: Add some kind  of debug or log!
            decorationPatternString = "er207";
    }
    return decorationPatternString;
}

String titleToString(Title t) {
    switch (t) {
        case BYPASS_MODE:    return " Bypass Mode ";
        case CONTINIUS_MODE: return " Continius Mode ";
        case MAIN_MENU:      return " Main Menu ";
        // TODO: Add some kind  of debug or log!
        default:             return "er218";
    }
}

String statusToString(Status s) {
    switch (s) {
        case ENGRAVING: return "ENGRAVING!";
        case PAUSE:     return "PAUSE!";
        // TODO: Add some kind  of debug or log!
        default:        return "er227";
    }
}