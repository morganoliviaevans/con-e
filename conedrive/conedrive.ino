// Define motor control pins
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>


const int IN1 = 16;
const int IN2 = 17;
const int ENA = 18;

const int IN3 = 19;
const int IN4 = 20;
const int ENB = 21;


bool isCenter = false;
bool isLeft = false;
bool isRight = false;


 // HardwareSerial dfSerial(1);  // Use UART1
 // DFRobotDFPlayerMini mp3;


void setup() {
  // Set pins as outpu
  Serial.begin(9600);
  //  dfSerial.begin(9600, SERIAL_8N1, 44, 43); // RX=9, TX=8
  delay(1000);
  Serial.print("we here");
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


  // if (!mp3.begin(dfSerial)) {
  // Serial.println("DFPlayer failed");
    // while(true);
  // }
  // mp3.volume(20);  // 0-30


}

void forward();
void stopMotor();
void backward();
void spin();
void rotateLeft();
void rotateRight();

void loop() {
  //mp3.playFolder1(1, 1);
 // delay(5000);  
  forward();
 // if (Serial.available() > 0) {
   // char command = Serial.read();
//hi meow :3
   // switch (command) {
    // case 'f': forward();     break;
    // case 's': stopMotor();   break;
    // case 'b': backward();    break;
    //case 'r': rotateRight(); break;
    //case 'l': rotateLeft();  break;
    //case 'p': spin();        break;

   // }
  //}
}

void spinAndPlay() {
  //mp3.play(3); // Play third MP3 file
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



