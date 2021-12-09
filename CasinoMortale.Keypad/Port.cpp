// 
// 
// 

#include "Port.h"

CasinoMortale::Port::Port(int rxPin, int txPin, const Keypad *keypad) : rxPin{ rxPin }, txPin{ txPin }, softwareSerial(rxPin, txPin), keypad{keypad}
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
		softwareSerial.begin(9600);
	}
	else if (isCommunicating && digitalRead(txPin) == LOW)
	{
		Serial.println("Jack removed.");
		isCommunicating = false;
		softwareSerial.end();
	}

	if (isCommunicating)
	{			
		char pinCode[7];
		keypad->getSavedPinCode(pinCode);

		Serial.print("Sending pin code ");
		Serial.print(pinCode);
		Serial.println(" over software serial port.");
		softwareSerial.println(pinCode);
	}
}
