#include "esp-speaker.h"
#include "esp-led.h"

// Objects and Rand Vars
Led led; // RGB Led obj
Speaker speaker;

unsigned long lastSoundTime = 0;
unsigned long nextSoundInterval = 0;


// Define motor control pins
const int IN1 = 16;
const int IN2 = 17;
const int ENA = 18;

const int IN3 = 19;
const int IN4 = 20;
const int ENB = 21;


bool isCenter = false;
bool isLeft = false;
bool isRight = false;


void rotateLeft();
//rotate 1 second

void setup() {
  // Set pins as output
  Serial.begin(9600);

  speaker.setup();
  led.setup();

  // seeding randomizer
  randomSeed(analogRead(A0));
  lastSoundTime = millis();
  nextSoundInterval = random(4000, 15000); // 8-10 sec

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Start with motor stopped
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0); // 0-255 (PWM)

  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(ENB, 0); // 0-255 (PWM)

}

void forward();
void stopMotor();
void backward();
void spin();
void rotateLeft();
void rotateRight();

void loop() {
  led.flash();
  if (Serial.available() > 0) {
    char command = Serial.read();
//hi meow :3
    switch (command) {
      case 'f': forward();
                led.setMode(Led::FLASH_GREEN);
                                            break;
      case 's': stopMotor();
                led.setMode(Led::FLASH_RED);
                speaker.playTrack(Speaker::WHEET_WHEW);
                                            break;
      case 'b': backward(); 
                led.setMode(Led::FLASH_RED);
                speaker.playTrack(Speaker::BACKUP);
                                            break;
      case 'r': rotateRight();              break;
      case 'l': rotateLeft();               break;
      case 'p': spin(); 
                led.setMode(Led::POLICE); 
                speaker.playTrack(Speaker::SIREN);
                                            break;
      case 'i': led.setMode(Led::IDLE);     break; // idle
      case 'a': led.setMode(Led::CYCLE);    break; // active
      case 'z': led.setMode(Led::SLEEP);    break; // sleep
    }
  }
  unsigned long now = millis();
  if(now - lastSoundTime >= nextSoundInterval) {
    int randomTrack = random(0, speaker.Sounds);
    speaker.playTrack((Speaker::Voiceline)randomTrack);

    lastSoundTime = now;
    nextSoundInterval = random(4000, 15000);
  }
}

void rotateLeft()
{

digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(ENA, 180); // 0-255 (PWM)
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
analogWrite(ENB, 180); // 0-255 (PWM)
}

void forward()
{

digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
analogWrite(ENA, 255); // 0-255 (PWM)
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
analogWrite(ENB, 255); // 0-255 (PWM)

/// led flashing
}

void backward()
{
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(ENA, 255); // 0-255 (PWM)
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENB, 255); // 0-255 (PWM)
}

void rotateRight()
{
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
analogWrite(ENA, 180); // 0-255 (PWM)
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENB, 180); // 0-255 (PWM)
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void spin() {

 rotateRight();
 delay(5000);
 stopMotor();
}
