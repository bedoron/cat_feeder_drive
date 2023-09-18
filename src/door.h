#ifndef DOOR_H
#define DOOR_H

#include <Arduino.h>

class Door {
    enum Motions { Idle, Opening, Open, Closing, Closed };
    Motions doorMovement;
    const uint8_t hbridge1;
    const uint8_t hbridge2;
    const uint8_t openSwitch;
    const uint8_t closedSwitch;
    const unsigned long closeWaitTicks;

    unsigned long closeWait;

    bool isOpen();

public:
    Door();
    void setup();
    void open();
    void close();
    void stop();
    void loopHandler();
};



#endif