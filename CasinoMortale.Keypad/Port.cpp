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
	softwareSerial = SoftwareSerial(rxPin, txPin);
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

	if (isCommunicating)
	{	
		char pinCode[7];
		keypad->getSavedPinCode(pinCode);

		Serial.print("Sending pin code ");
		Serial.print(pinCode);
		Serial.println(" over software serial port.");
				
		softwareSerial.begin(4800);
		softwareSerial.flush();
		softwareSerial.print("*");
		softwareSerial.print(pinCode);
		softwareSerial.print("#");
		softwareSerial.flush();
		softwareSerial.end();		
	}
}
