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
    void flash();
    void setMode(LightMode newMode);

private:
    // Current mode and timing
    LightMode currMode = IDLE;
    unsigned long currMillis = 0;
    unsigned long lastModeSwitch = 0;

    // Pulse Yellow (Idle Mode)
    static constexpr int maxBright = 255;
    static constexpr int pulseDelay = 10;
    int brightness = 1;
    int redBrightness = 0;
    int greenBrightness = 0;
    int blueBrightness = 0;
    int fadeAmt = 1;
    unsigned long lastUpdate = 0;

    // Police Mode
    bool redOn = true;
    unsigned long lastFlash = 0;
    static constexpr unsigned long flashInterval = 200;

    // Mode logic
    void pulse_yellow();
    void police();
};

#endif