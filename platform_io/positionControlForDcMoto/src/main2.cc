#include <Arduino.h>

// Define the interrupt pins and the count variable
const int interruptPin1 = 2;
const int interruptPin2 = 3;
volatile long encoderCount = 0;

void setup()
{
    // Set the interrupt pins as inputs
    pinMode(interruptPin1, INPUT);
    pinMode(interruptPin2, INPUT);

    // Attach the ISRs to the interrupt pins
    attachInterrupt(digitalPinToInterrupt(interruptPin1), onInterrupt1, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(interruptPin2), onInterrupt2, CHANGE);
}

void loop()
{
    // Your main code goes here
}


/* x2 encoding */
void onInterrupt1()
{
    int state = digitalRead(2);

    if(digitalRead(2) == state && digitalRead(3) == !state)
        ++encoderCount;

    int state = digitalRead(2);

    if(digitalRead(2) == state && digitalRead(3) == state)
        --encoderCount;

}

/* refactored the above code  */
void onInterrupt1()
{
    int state = digitalRead(2);

    if(digitalRead(3) == ~state)
        ++encoderCount;

    int state = digitalRead(2);

    if(digitalRead(3) == state)
        --encoderCount;

}
