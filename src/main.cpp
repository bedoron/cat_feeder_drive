#include <Arduino.h>
#include "door.h"
 
/*
  Simple Blink sketch
  simple-blink.cpp
  Use for PlatformIO demo
 
  From original Arduino Blink Sketch
  https://www.arduino.cc/en/Tutorial/Blink
  
  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/
 
// Set LED_BUILTIN if undefined or not pin 13
// #define LED_BUILTIN 13


Door door = Door();

void setup()
{
  // Initialize LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  door.setup();
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A7, INPUT);
  pinMode(A6, INPUT);

  Serial.begin( 9600 );
  while(!Serial);
}


char buffer[1024];
void loop()
{
  static int previousOpenDoor = 1;
  int openDoor = digitalRead(A5);
  if (previousOpenDoor != openDoor) {
    previousOpenDoor = openDoor;
    sprintf(buffer, "Open door value changed: %d", openDoor);
    Serial.println(buffer);

    if (openDoor == 0) {
      door.open();
    }
  }


  static int previousCloseDoor = 1;
  int closeDoor = digitalRead(A4);
  if (previousCloseDoor != closeDoor) {
    previousCloseDoor = closeDoor;
    sprintf(buffer, "Close door value changed: %d", closeDoor);
    Serial.println(buffer);

    if (closeDoor == 0) {
      door.close();
    }
  }

  door.loopHandler();

  // int openDoor = digitalRead(A6);
  // if (openDoor == 0) {
  //   sprintf(buffer, "Open button pushed: %d", openDoor);
  //   Serial.println(buffer);
  //   door.open();
  // }

  // int closeDoor = digitalRead(A7);
  // if (closeDoor == 0) {
  //   sprintf(buffer, "Close button pushed: %d", closeDoor);
  //   Serial.println(buffer);
  //   door.close();
  // }

  // door.loopHandler();

  // Set the LED HIGH
  // digitalWrite(LED_BUILTIN, HIGH);
 
  // // Wait for a second
  // delay(500);
 
  // digitalWrite(LED_BUILTIN, LOW);
  
  // delay(500);

  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(500);
  // // Set the LED LOW
  // digitalWrite(LED_BUILTIN, LOW);
 
  //  // Wait for a second
  // delay(1000);
}