#include <Arduino.h>
#include <avr/power.h>

#define SYSTEM_IO_PORT PORTA
#define SYSTEM_IO_PIN PINA
#define IS_OPEN_LED PA7
#define IS_CLOSED_LED PA5
#define TRIGGER_CHECK_PIN PINA4

const int led = 0;
const int sleep = 1000;


// the setup routine runs once when you press reset:
void setup() {
    clock_prescale_set(clock_div_1);
    // Set indicator outputs
    bitSet(DDRA, IS_CLOSED_LED); 
    bitSet(DDRA, IS_OPEN_LED);
    bitClear(DDRA, TRIGGER_CHECK_PIN); // Read pulse state
}

// the loop routine runs over and over again forever
void flashLeds(bool isOpen) {
  if (isOpen) {
    bitClear(SYSTEM_IO_PORT, IS_OPEN_LED);
    bitSet(SYSTEM_IO_PORT, IS_CLOSED_LED);
  } else {
    bitClear(SYSTEM_IO_PORT, IS_CLOSED_LED);
    bitSet(SYSTEM_IO_PORT, IS_OPEN_LED);
  }
}

static bool ledsState = true;
static bool canChangeState = true;

void loop() {
  /*
    1. Move check to ISR
    2. Implement state machine to ceck switch status
    3. Add low power support 
  */
  unsigned long delayTime = 250;
  if (bitRead(SYSTEM_IO_PIN, TRIGGER_CHECK_PIN)) {
    delayTime = 1000;
  } 

  flashLeds(ledsState);
  if (canChangeState) {
    ledsState = !ledsState;
  }

  delay(delayTime);
}