#include "esp-speaker.h"
#include "esp-led.h"

Speaker speaker;  // Declare the object globally so loop() can use it too
Led led;          // RGB Led obj

void setup() {
  Serial.begin(115200);
  // speaker.setup();
  led.setup();
}

void loop() {
  // speaker.playTrack(Speaker::HELLO1);
  // delay(4000);
  // speaker.playTrack(Speaker::OKAY);
  // delay(4000);
  led.flash(Led::IDLE);
}