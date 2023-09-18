#include "door.h"

static unsigned long _closeWaitTicks = 150000;


Door::Door(): doorMovement(Idle), hbridge1(A2), hbridge2(A3), openSwitch(A0), closedSwitch(A1), closeWaitTicks(_closeWaitTicks) {

}

void Door::setup() {
    pinMode(openSwitch, INPUT);
    pinMode(closedSwitch, INPUT);
    pinMode(hbridge1, OUTPUT);
    pinMode(hbridge2, OUTPUT);
}

void Door::open() {
    Serial.println("Open door command");

    doorMovement = Opening;
    digitalWrite(hbridge1, HIGH);
    digitalWrite(hbridge2, LOW);
}

void Door::close() {
    Serial.println("Close door command");

    doorMovement = Closing;
    closeWait = 0;
    digitalWrite(hbridge1, LOW);
    digitalWrite(hbridge2, HIGH);
}

void Door::stop() {
    // Do stop stuff here
    Serial.println("Stopping door");
    digitalWrite(hbridge1, HIGH);
    digitalWrite(hbridge2, HIGH);
}

bool Door::isOpen() {
    // Check if door is open
    return digitalRead(openSwitch) == HIGH ? false : true;
}

void Door::loopHandler() {
    switch (doorMovement)
    {
    case Opening:
        if (isOpen()) {
            Serial.println("Door is now open, stopping");
            doorMovement = Open;
            stop();
        }

        break;
    case Closing:
        if (closeWait < closeWaitTicks) {
            ++closeWait;
            break;
        } 
        Serial.println("Door is now closed, stopping");
        doorMovement = Closed;
        stop();
        break;
    default:
        break;
    }
}