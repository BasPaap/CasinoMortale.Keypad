#include "Led.h"

Bas::Led::Led(int pin) : pin{ pin }
{
}

void Bas::Led::initialize()
{
    Serial.print("Initializing LED on pin ");
    Serial.println(this->pin);
    pinMode(this->pin, OUTPUT);
}

void Bas::Led::turnOn()
{    
    digitalWrite(this->pin, HIGH);
}


void Bas::Led::turnOff()
{    
    digitalWrite(this->pin, LOW);
}
