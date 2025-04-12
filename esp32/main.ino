#include "esp-speaker.h"

Speaker speaker;

void setup() {
  Serial.begin(115200);

  speaker.setup();
  delay(4000);
}

void loop() {
  
}
