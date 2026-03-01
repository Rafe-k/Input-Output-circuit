#include <Servo.h>

Servo myservo;
const int In1 = 8;
const int In2 = 11;
const int EnA = 5;
const int pot = A0;
const int trig = A1;
const int echo = A2;
const int buzz = 4;
const int bbtn = A3;  
const int led = 6;
const int sound = A5;
int sinepitch = 0;

void setup() {
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  pinMode(sound, INPUT);

  myservo.attach(3);
  Serial.begin(9600);
  
}

void goStraight(int val) {

  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed between 150 and 255
  analogWrite(EnA, val);
}

void goReverse(int val) {
  digitalWrite(In1, LOW);

  digitalWrite(In2, HIGH);
  // set speed between 150 and 255

  analogWrite(EnA, val);
}
void loop() {
  int val = analogRead(pot);

  // sets speed for servo depending on potentiometer rotation
  val = map(val, 0, 1023, 0, 300);

  // turns on servo
  myservo.write(val);

  long duration, cm;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  

  duration = pulseIn(echo, HIGH);
  cm = distanceConvert(duration);
  int dis = map(cm, 0, 1023, 0, 100);
  
  // a map for the ultra sensor 
  long leddis = map(cm,0,200,255,0);

  if (leddis < 0) {
    leddis = 0;
  }

  Serial.println(leddis);
  
  // turns on led
  analogWrite(led,leddis);

  // bool for checking if button is pressed
  bool pressed = digitalRead(bbtn);
  
  sinepitch += 1;

  float buzzspeed = analogRead(pot);
  buzzspeed = map(buzzspeed,0,1023,0,10);
  
  // sets pitch for button using a sine wave
  float pitch = (500*sin((buzzspeed/100)*sinepitch) + 1500);
  
  // sets speed for motor
  int motorsound = map(analogRead(sound),0,500,0,250);


  // turns on/off button and determined motor spin direction
  if (pressed) {
    tone(buzz,pitch);
    goReverse(motorsound);
  } else {
    goStraight(motorsound);
    noTone(buzz);
  }

  //delay(50);

}

long distanceConvert(long microSeconds) {
  return microSeconds / 29 / 2;
}
