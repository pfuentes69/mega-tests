#include <Arduino.h>

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int val; 

void setup() {
  myservo.attach(13);  // attaches the servo on pin 9 to the servo object
  Serial.begin(115200);
  for (val=0; val<=120; val+=1) {
    Serial.println(val);
    myservo.write(val);                  // sets the servo position according to the scaled value
    delay(20);                           // waits for the servo to get there
  }
  for (val=120; val>=0; val-=1) {
    Serial.println(val);
    myservo.write(val);                  // sets the servo position according to the scaled value
    delay(20);                           // waits for the servo to get there
  }
  myservo.write(60);
  delay(100);
  myservo.detach();
}

void loop() {
}