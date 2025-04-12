#include "esp-led.h"

void Led::setup()
{
    pinMode(PIN_RGB_R, OUTPUT);
    pinMode(PIN_RGB_G, OUTPUT);
    pinMode(PIN_RGB_B, OUTPUT);

    digitalWrite(PIN_RGB_R, LOW);
    digitalWrite(PIN_RGB_G, LOW);
    digitalWrite(PIN_RGB_B, LOW);
    delay(500);

}

// -- non-blocking time var -- //
unsigned long prevMillis = 0;
unsigned long currMillis = 0;

void Led::flash(LightMode action)
{
    currMillis = millis();
    if(currMillis - prevMillis < 300)
        return;

    switch (action) {
        case IDLE:
            pulse_yellow();
            break;
        case POLICE:
            police();
            break;
    }
} 

// -- Analog Brightness: 0 -> 255 -- //
const int maxBright = 255;
int brightness = 1;
int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;
int fadeAmt = 1;
unsigned long lastUpdate = 0;
const int pulseDelay = 10;

void Led::pulse_yellow() 
{
    currMillis = millis();
    if (currMillis - lastUpdate >= pulseDelay) {
        lastUpdate = currMillis;

        if(brightness <= 0 || brightness >= 255)
            fadeAmt = -fadeAmt;

        // Set brightnesses
        analogWrite(PIN_RGB_R, redBrightness);
        analogWrite(PIN_RGB_G, greenBrightness);
        analogWrite(PIN_RGB_B, 0);

        brightness += fadeAmt;
        redBrightness = brightness;
        greenBrightness = static_cast<int>(brightness * .85);
    }
}