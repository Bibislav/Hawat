#ifndef DISPLAY_H
#define DISPLAY_H

void initDisplay();
void clearDisplay();
void clearRow(int row);
void setCursorAtOrigin();
bool checkBoundary(int x, int y);
void setCursorAtTheSpecificPosition(int x, int y);
void setCursorAtTheBeginningOfARow(int y);
void setCursorAtTheEndOfARow(int y);
void fillRowWith(char c, int row);
void fillColumnWith(char c, int column);
void createBorder();
void createBorder(char c);
void initialScreen();
void initialScreen(float sleepSeconds);


#endif