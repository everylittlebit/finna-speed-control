#include <Arduino.h>
#include "TeensyThreads.h"
#include <Cmd.h>



//Pin defs

const byte red = 10;
const byte green = 11;
const byte blue = 12;
const byte yPin = 20;
const byte xPin = 18;
const byte lFan = 19;
const byte rFan = 17;
const byte flapPot = 15;
const byte aFlap = 13;
const byte bFlap = 14;

int readPot(char axis, bool hiRes) {
  int res = 255;
  if (hiRes) {
    res = 1023;
  }

  if (axis == 'y') {
    return map (analogRead(yPin), 0, 1024, res, 0);
  }
  else if (axis == 'x') {
    return map (analogRead(xPin), 0, 1024, 0, res);
  }
  else {
    Serial.println("ERROR IN readPot");
    return 0;
  }
}

int setVarDirection(int location)
{
  if (readPot('x', 1) >= 1, readPot('x', 1) <= 509) {
    digitalWrite (aFlap, HIGH);
    while (1) {
      if (analogRead(flapPot) > location) {
        digitalWrite (aFlap, LOW);
        break;
      }
      else {

      }
    }
  }
  else if (readPot('x', 1) >= 516, readPot('x', 1) <= 1024) {
    digitalWrite (bFlap, HIGH);
    while (1) {
      if (analogRead(flapPot) < location) {
        break;
      }
    }
  }
    else if (readPot('x', 1) >= 510, readPot('x', 1) <= 515) {
      digitalWrite (flapPot, LOW);
    }
    else {
    }
  }

void setFanSpeed() {
  int tempPot = readPot('y',1);
  analogWrite(lFan, tempPot);
  analogWrite(rFan, tempPot);
}


void setup() {
  cmdInit(9600);
  digitalWrite(red, HIGH);
  delay(200);
  digitalWrite(blue, HIGH);
  delay(200);
  digitalWrite(green, HIGH);
  delay(500);
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
}
void loop() {
  threads.addThread(setFanSpeed());
  threads.addThread(setVarDirection(readPot('x'));
                    delay(1000);
}
