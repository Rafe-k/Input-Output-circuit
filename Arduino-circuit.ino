#include <Servo.h>

Servo myservo;
const int In1 = 8;
const int In2 = 11;
const int EnA = 3;
const int pot = A0;
const int trig = A1;
const int echo = A2;
const int buzz = 4;
const int bbtn = A3;  
const int led = 6;
const int sound = A5;
float sinepitch = 0;

void setup() {
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  pinMode(sound, INPUT);

  myservo.attach(5);
  Serial.begin(9600);
  
}

void goStraight(int val) {

  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed between 150 and 255
  analogWrite(EnA, val);


  //delay(2000);

  // now turn off motors

  // digitalWrite(In1, LOW);

  // digitalWrite(In2, LOW);
}

void goReverse(int val) {
  digitalWrite(In1, LOW);

  digitalWrite(In2, HIGH);
  // set speed between 150 and 255

  analogWrite(EnA, val);
}
void loop() {
  int val = analogRead(pot);

  val = map(val, 0, 1023, 0, 300);

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
  

  int leddis = map(cm,0,200,255,0);
  

  

  analogWrite(led,leddis);

  bool pressed = digitalRead(bbtn);
  
  sinepitch += 1;

  float pitch = (500*sin(0.5*sinepitch) + 1500);
  Serial.println(pitch);

  if (pressed == true){
   	tone(buzz, pitch);
  } else if (pressed == false){
    noTone(buzz);
  }
  

  int motorsound = map(analogRead(sound),0,1023,0,250);

  //Serial.println(motorsound);
  if (pressed) {
    goReverse(motorsound);
  } else {
    goStraight(motorsound);
  }

  delay(50);

}

long distanceConvert(long microSeconds) {
  return microSeconds / 29 / 2;
}
