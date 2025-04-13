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

// this runs forever in loop()
void Led::flash()
{
    currMillis = millis();

    switch (currMode) {
        case IDLE:
            pulse_yellow();
            break;
        case POLICE:
            police();
            break;
    }
} 

void Led::setMode(LightMode newMode)
{
    if (newMode != currMode) {
        currMode = newMode;
        lastModeSwitch = millis();

        // Reset mode-specific state
        brightness = 1;
        redBrightness = 0;
        greenBrightness = 0;
        blueBrightness = 0;
        fadeAmt = 1;
        lastUpdate = 0;
    }
}

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

void Led::police() 
{
    currMillis = millis();
    if(currMillis - lastFlash >= flashInterval) {
        lastFlash = currMillis;
        digitalWrite(PIN_RGB_G, LOW);

        if(redOn) {
            digitalWrite(PIN_RGB_R, HIGH);
            digitalWrite(PIN_RGB_B, LOW);
        } else {
            digitalWrite(PIN_RGB_R, LOW);
            digitalWrite(PIN_RGB_B, HIGH);
        }

        redOn = !redOn;
    }
}