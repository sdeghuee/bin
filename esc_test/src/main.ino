#include "Arduino.h"
#include "Servo.h"

Servo myservo;

int val = 90;

void setup()
{
    Serial.begin(9600);
    myservo.attach(9);
}

void loop()
{
    val = Serial.read();
    myservo.write(val);
    delay(15);
}

