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

void loop() {
forward();
delay(5000);
backward();
delay(5000);
}

void rotateLeft()
{

digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(ENA, 100); // 0-255 (PWM)
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
analogWrite(ENB, 100); // 0-255 (PWM)
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
analogWrite(ENA, 100); // 0-255 (PWM)
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENB, 100); // 0-255 (PWM)
}
