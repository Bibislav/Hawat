#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

enum PossibleAlign {
    CENTER,
    LEFT,
    RIGHT
};

enum DecorationPattern {
    ARROW, // >>>>> ... <<<<<
    STAR, // ***** ... *****
    LINE // ---- ... ----
};

enum Title {
    BYPASS_MODE,
    CONTINIUS_MODE,
    MAIN_MENU
};

enum Status {
    ENGRAVING,
    PAUSE
};

void initDisplay();
void clearDisplay();
void setCursorAtOrigin();
bool checkBoundary(int x, int y);
void setCursorAtTheSpecificPosition(int x, int y);
void setCursorAtTheBeginningOfARow(int y);
void setCursorAtTheEndOfARow(int y);
void fillRowWith(char c, int row);
void fillColumnWith(char c, int column);
void clearRow(int row);
void clearColumn(int column);
void printLineToRow(String s, int row);
void createBorder();
void createBorder(char decorationPattern);
void printAlignedText(const String &s, int row, PossibleAlign selectedAlign);
void addTitle(Title title, DecorationPattern decorationPattern);
void addStatusMessage(Status status, DecorationPattern decorationPattern);
String generateDecorationPattern(DecorationPattern d);
String titleToString(Title t);
String statusToString(Status s);


#endif