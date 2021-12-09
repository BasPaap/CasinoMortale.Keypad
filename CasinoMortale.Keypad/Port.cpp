// 
// 
// 

#include "Port.h"

CasinoMortale::Port::Port(int rxPin, int txPin) : rxPin{ rxPin }, txPin{ txPin }
{
}

void CasinoMortale::Port::initialize()
{
	Serial.println("Initializing port.");
	pinMode(txPin, INPUT_PULLUP);
}

void CasinoMortale::Port::update()
{
	if (!isCommunicating && digitalRead(txPin) == HIGH)
	{
		Serial.println("Jack connected");
		isCommunicating = true;
	}
	else if (isCommunicating && digitalRead(txPin) == LOW)
	{
		Serial.println("Jack removed.");
		isCommunicating = false;
	}
}
