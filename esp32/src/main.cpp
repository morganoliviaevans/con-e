#include "esp-speaker.h"

Speaker speaker;  // Declare the object globally so loop() can use it too

void setup() {
  Serial.begin(115200);
  speaker.setup();
  delay(4000);  // Optional delay before playback starts
}

void loop() {
  speaker.playTrack(Speaker::HELLO1);
  delay(4000);
  speaker.playTrack(Speaker::OKAY);
  delay(4000);
}