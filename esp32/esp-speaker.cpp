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
  delay(4000);

  Serial.println(player.readFileCounts());
  Serial.println(player.readCurrentFileNumber());
}

// Playtrack time bounce
static unsigned long lastPlayTime = 0;
unsigned long currentTime = 0;

void Speaker::playTrack(Voiceline sound) 
{
  currentTime = millis();
  if(currentTime - lastPlayTime >= 5000) {
    player.playFolder(1, sound);
    lastPlayTime = currentTime;
  }
}