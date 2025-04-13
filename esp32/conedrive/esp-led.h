#ifndef LED_H
#define LED_H

#include <Arduino.h>

constexpr int PIN_RGB_R = 36;
constexpr int PIN_RGB_G = 37;
constexpr int PIN_RGB_B = 38;

class Led {
public:
    const long Modes = 6;
    enum LightMode {
        IDLE, // yellow pulse
        POLICE, // b, r
        FLASH_RED,
        FLASH_GREEN, // active
        SLEEP, // blue pulse
        CYCLE // cycles r, g, b
    };

    void setup();
    void flash();
    void setMode(LightMode newMode);

private:
    // Current mode and timing
    LightMode currMode = IDLE;
    unsigned long currMillis = 0;
    unsigned long lastModeSwitch = 0;

    // Pulse Yellow/Blue
    static constexpr int maxBright = 255;
    static constexpr int pulseDelay = 10;
    int brightness = 1;
    int redBrightness = 0;
    int greenBrightness = 0;
    int blueBrightness = 0;
    int fadeAmt = 1;
    unsigned long lastUpdate = 0;

    // Police and Flash Red Mode
    bool redOn = true;
    bool greenOn = true;
    unsigned long lastFlash = 0;
    static constexpr unsigned long flashInterval = 200;

    // Cycle Mode
    int currOn = 0; // 0 red, 1 green, 2 blue
    unsigned long lastCycle = 0;
    static constexpr unsigned long cycleInterval = 300;

    // Mode logic
    void pulse_yellow();
    void pulse_blue();
    void police();
    void flash_red();
    void flash_green();
    void cycle();
};

#endif