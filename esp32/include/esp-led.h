#ifndef LED_H
#define LED_H

#include <Arduino.h>

constexpr int PIN_RGB_R = 5;
constexpr int PIN_RGB_G = 6;
constexpr int PIN_RGB_B = 7;


class Led {
public:

    enum LightMode {
        IDLE,
        POLICE
    };
    void setup();
    void flash(LightMode action);

private:    

    void pulse_yellow();
    void idle();
    void police();
};

#endif