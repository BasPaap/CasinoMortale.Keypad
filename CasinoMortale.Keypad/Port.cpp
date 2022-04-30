// 
// 
// 

#include "Port.h"

CasinoMortale::Port::Port(int rxPin, int txPin, const Keypad *keypad) : rxPin{ rxPin }, txPin{ txPin }, softwareSerial(rxPin, txPin), keypad{keypad}
{	
}

void CasinoMortale::Port::initialize(CallbackPointer unlockedCallback, int difficultyLevel)
{
	Serial.println("Initializing port.");
	this->unlockedCallback = unlockedCallback;
	this->difficultyLevel = difficultyLevel;
	pinMode(txPin, INPUT_PULLUP);
	softwareSerial = SoftwareSerial(rxPin, txPin);
}

void CasinoMortale::Port::update()
{
	if (!isCommunicating && digitalRead(txPin) == HIGH)
	{
		Serial.println("Jack connected");
		isCommunicating = true;				
		softwareSerial.begin(4800);
		softwareSerial.flush();
	}
	else if (isCommunicating && digitalRead(txPin) == LOW)
	{
		Serial.println("Jack removed.");
		isCommunicating = false;		
		isUnlockReceived = false;
		softwareSerial.end();
	}

	if (!isUnlockReceived && isCommunicating)
	{	
		char pinCode[7];
		keypad->getSavedPinCode(pinCode);

		Serial.print("Sending pin code ");
		Serial.print(pinCode);
		Serial.println(" over software serial port.");
		
		softwareSerial.print("*");
		softwareSerial.print(difficultyLevel);
		softwareSerial.print(pinCode);
		softwareSerial.print("#");
		softwareSerial.flush();
	
		if (softwareSerial.available())
		{
			char readValue = softwareSerial.read();
			if (readValue == 'U')
			{
				Serial.print("Received unlock message on port.");
				isUnlockReceived = true;
				this->unlockedCallback();
			}
		}
	}
}
