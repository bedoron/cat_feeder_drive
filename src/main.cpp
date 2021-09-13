#include <Arduino.h>
#include <avr/power.h>

#define SYSTEM_IO_PORT PORTA
#define SYSTEM_IO_PIN PINA
#define IS_OPEN_LED PA7
#define IS_CLOSED_LED PA5
#define TRIGGER_CHECK_PIN PINA4
#define TRIGGER_CHECK_PCINT PCINT4
#define TRIGGER_CHECK_PCMSK PCMSK0 

enum CDStates {
  WAIT_FOR_INPUT,
  CS_ENABLE,
  CS_DISABLE,

  OPEN_DOOR,
  IS_OPEN_CHARGE,
  IS_OPEN_WAIT,
  IS_OPEN_CHECK,
  
  CLOSE_DOOR,
  IS_CLOSED_CHARGE,
  IS_CLOSED_WAIT,
  IS_CLOSED_CHECK
};

CDStates state = WAIT_FOR_INPUT;

#define DELAY_STEP 100
#define MAX_DELAY 1100

unsigned long delayTime = 5;
unsigned short speedSet = 0;

ISR(PCINT0_vect) {
  if (bitRead(SYSTEM_IO_PIN, TRIGGER_CHECK_PIN)) {

    switch (speedSet) {
    case 0:
      delayTime = 1;
      break;
    case 1:
      delayTime = 5;
      break;
    case 2:
      delayTime = 10;
      break;
    case 3:
      delayTime = 100;
      break;
    case 4:
      delayTime = 500;
      break;
    default:
      speedSet = 0;
    }

    speedSet = (speedSet + 1) % 5;
    // If IDLE - Open Door + Start timer to shutdown
    // If NOT IDLE - reset timer to shutdown
    // delayTime = (delayTime + DELAY_STEP) % MAX_DELAY;
  }
}

// the setup routine runs once when you press reset:
void setup() {
    clock_prescale_set(clock_div_1);
    // Set indicator outputs
    bitSet(DDRA, IS_CLOSED_LED); 
    bitSet(DDRA, IS_OPEN_LED);
    bitClear(DDRA, TRIGGER_CHECK_PIN); // Read pulse state

    // Enable interrupts
    bitSet(GIMSK, PCIE0); // Enable Pin Change interrupts
    GIFR = B00000000; // Clear state
    bitSet(TRIGGER_CHECK_PCMSK, TRIGGER_CHECK_PCINT); // Enable pin specific interrupt
    bitSet(SREG, SREG_I); // Enable interrupts
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

void loop() {
  /*
    2. Implement state machine to check switch status
    3. Add low power support 
  */

  flashLeds(ledsState);
  ledsState = !ledsState;
  delay(delayTime);
}