#include <Arduino.h>

const int led = 0;
const int sleep = 1000;


// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  // bitSet(DDRB, led);
  pinMode(PB0, OUTPUT);
  digitalWrite(PB0, 0);
}

// the loop routine runs over and over again forever
void loop() {
  pinMode(PB4, OUTPUT); // Configure PB4 as output
  digitalWrite(PB4, 1); // Charge capacitor
  delay(1); // wait for capacitor to charge

  pinMode(PB4, INPUT); // Configure PB4 as input
  bool isOpenCircuit = (digitalRead(PB4) == 1); // Read state of capacitor load
  if (isOpenCircuit) {
    digitalWrite(PB0, 1);
  } else {
    digitalWrite(PB0, 0);
  }

  delay(500);
}