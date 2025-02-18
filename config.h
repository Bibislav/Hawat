#ifndef CONFIG_H
#define CONFIG_H

#define VERSION "ver 2.5.0"

// Toggle switch that pause engraving. Sort of a safty switch.
#define PAUSE_SWITCH_PIN 14

// Pedal on the floar that starts engraving sequence.
#define FOOT_SWITCH_PIN 16

// Nub for interacting with Hawat. Check rotary encoder pinout. Usuly out_A or something like that.
#define ROTARY_ENCODER_PIN_A 5
#define ROTARY_ENCODER_PIN_B 6
#define ROTARY_ENCODER_BUTTON_PIN 4

// Pins that goes to stepper controler. Check your controler for DIR and PULL input.
#define STEPPER_PULL_PIN 3
#define STEPPER_DIRECTION_PIN 2

// Output from Hawat that stats engraving. Conects to engraving machine itself.
#define START_ENGRAVING_PIN 15

// Pins that goes to LCD. Check your LCD datasheet.
#define LCD_RS_PIN 12
#define LCD_EN_PIN 11
#define LCD_D4_PIN 10
#define LCD_D5_PIN 9
#define LCD_D6_PIN 8
#define LCD_D7_PIN 7

// Number of rows and columns of LCD
#define LCD_ROWS 4
#define LCD_COLUMNS 20

#endif