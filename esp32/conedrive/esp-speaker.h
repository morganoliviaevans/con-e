#ifndef SPEAKER_H
#define SPEAKER_H

#include <HardwareSerial.h>
#include "DFRobotDFPlayerMini.h"

// Use pins 20 and 21 with HardwareSerial to communicate with DFPlayer Mini
const int PIN_MP3_RX = 16; // Connects to module's RX -- GPIO 16
const int PIN_MP3_TX = 17; // Connects to module's TX -- GPIO 17

class Speaker {
public:
  const int Sounds = 17;
  enum Voiceline {
    STARTUP = 1,
    HELLO1,
    OKAY,
    SIREN,
    HELLO3,
    LOADUP,
    BACKUP,
    WHEET_WHEW,
    ULT1,
    ULT2,
    DANCE,
    FALL,
    SING,
    SING2,
    EXTERMINATE,
    R2BEEP,
    R2SCREAM
  };

  Speaker();
  void setup();                // Initializes the speaker
  void playTrack(Voiceline sound);   // Plays a specific track
  DFRobotDFPlayerMini player;     // DFPlayer object


private:
    HardwareSerial dfplayerSerial;  // Hardware serial for DFPlayer Mini
};

#endif