#include "config.h"
#include <Rotary.h>
#include <JC_Button.h>

// When impt_x is done, this will be removed
#include "screen.h"

Rotary encoder(ROTARY_ENCODER_PIN_A, ROTARY_ENCODER_PIN_B);
Button button(ROTARY_ENCODER_BUTTON_PIN, true, true);

unsigned position = 0;

void initRotaryEncoder() {
    button.begin();
}

// This function will be called when the rotary encoder is connected to interrupt pins and will return the position.
// Until then, it is what it is. (impr_x)
unsigned short int selectLoop() {
    while (1)
    {
        unsigned char result = encoder.process();
        button.read();
        if (result == DIR_CW) { 
            if (position < 2) position += 1;
            else if (position == 2) position = 0;
            mainMenuScreen(position);
        }
        if (result == DIR_CCW) {
            if (position > 0) position -= 1;
            else if (position == 0) position = 2;
            mainMenuScreen(position);
        }
        if (button.wasPressed()) {
            return position;
        }

        // if (button.pressedFor(1000))
        // {
        //     welcomeScreen();
        // }
        
    }
}