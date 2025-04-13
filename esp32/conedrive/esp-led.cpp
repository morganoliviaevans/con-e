#include "esp-led.h"

void Led::setup()
{
    pinMode(PIN_RGB_R, OUTPUT);
    pinMode(PIN_RGB_G, OUTPUT);
    pinMode(PIN_RGB_B, OUTPUT);

    digitalWrite(PIN_RGB_R, LOW);
    digitalWrite(PIN_RGB_G, LOW);
    digitalWrite(PIN_RGB_B, LOW);

    setMode(Led::IDLE);
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
        case FLASH_RED:
            flash_red();
            break;
        case FLASH_GREEN:
            flash_green();
            break;
        case SLEEP:
            pulse_blue();
            break;
        case CYCLE:
            cycle();
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

void Led::pulse_blue() 
{
    currMillis = millis();
    if (currMillis - lastUpdate >= pulseDelay) {
        lastUpdate = currMillis;

        if(brightness <= 0 || brightness >= 255)
            fadeAmt = -fadeAmt;

        // Set brightnesses
        analogWrite(PIN_RGB_R, 0);
        analogWrite(PIN_RGB_G, 0);
        analogWrite(PIN_RGB_B, blueBrightness);

        brightness += fadeAmt;
        blueBrightness = brightness;
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

void Led::flash_red()
{
    currMillis = millis();

    if (currMillis - lastFlash >= flashInterval) {
        lastFlash = currMillis;

        redOn = !redOn;
        digitalWrite(PIN_RGB_R, redOn ? HIGH : LOW);

        digitalWrite(PIN_RGB_G, LOW);
        digitalWrite(PIN_RGB_B, LOW);
    }
}

void Led::flash_green()
{
    currMillis = millis();

    if (currMillis - lastFlash >= flashInterval) {
        lastFlash = currMillis;

        greenOn = !greenOn;
        digitalWrite(PIN_RGB_G, greenOn ? HIGH : LOW);

        digitalWrite(PIN_RGB_R, LOW);
        digitalWrite(PIN_RGB_B, LOW);
    }
}

void Led::cycle()
{
    currMillis = millis();
    if(currMillis - lastCycle >= cycleInterval) {
        lastCycle = currMillis;
        if(currOn == 0) {
            digitalWrite(PIN_RGB_R, HIGH);
            digitalWrite(PIN_RGB_G, LOW);
            digitalWrite(PIN_RGB_B, LOW);
            currOn = 1;
        } else if (currOn == 1) {
            digitalWrite(PIN_RGB_R, LOW);
            digitalWrite(PIN_RGB_G, HIGH);
            digitalWrite(PIN_RGB_B, LOW);
            currOn = 2;
        } else {
            digitalWrite(PIN_RGB_R, LOW);
            digitalWrite(PIN_RGB_G, LOW);
            digitalWrite(PIN_RGB_B, HIGH);
            currOn = 0;
        }
    }
}