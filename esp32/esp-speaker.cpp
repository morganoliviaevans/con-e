#include "esp-speaker.h"

Speaker::Speaker()
  : dfplayerSerial(1) // initialize UART1 
  {}

void Speaker::setup() 
  {
  dfplayerSerial.begin(9600, SERIAL_8N1, PIN_MP3_RX, PIN_MP3_TX);
  delay(1000);

  if (!player.begin(dfplayerSerial)) {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  player.volume(30);
  playTrack(Speaker::STARTUP);
  delay(2000);

  Serial.println(player.readFileCounts());
  Serial.println(player.readCurrentFileNumber());
}

void Speaker::playTrack(Sound sound) 
  {
  player.play(sound);
  }