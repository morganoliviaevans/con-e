#ifndef SPEAKER_H
#define SPEAKER_H

#include <HardwareSerial.h>
#include "DFRobotDFPlayerMini.h"

// Use pins 20 and 21 with HardwareSerial to communicate with DFPlayer Mini
const int PIN_MP3_RX = 20; // Connects to module's RX
const int PIN_MP3_TX = 21; // Connects to module's TX

class Speaker {
public:
  enum Sound {
    STARTUP = 1,
    HELLO1,
    OKAY
  };
  Speaker();
  void setup();                // Initializes the speaker
  void playTrack(Sound sound);   // Plays a specific track

private:
    HardwareSerial dfplayerSerial;  // Hardware serial for DFPlayer Mini
    DFRobotDFPlayerMini player;     // DFPlayer object
};

#endif
