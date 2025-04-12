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
  // Set pins as outpu
  Serial.begin(9600);

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
  if (Serial.available() > 0) {
    char command = Serial.read();
//hi meow :3
    switch (command) {
      case 'f': forward();     break;
      case 's': stopMotor();   break;
      case 'b': backward();    break;
      case 'r': rotateRight(); break;
      case 'l': rotateLeft();  break;
      case 'p': spin();        break;

    }
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
