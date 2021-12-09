// Port.h

#ifndef _PORT_h
#define _PORT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<SoftwareSerial.h>
#include "Keypad.h"

namespace CasinoMortale
{
	class Port
	{
		using CallbackPointer = void(*)();
		int rxPin;
		int txPin;
		bool isCommunicating;
		SoftwareSerial softwareSerial;
		Keypad *keypad;
		bool isUnlockReceived;
		CallbackPointer unlockedCallback;

	public:
		Port(int rxPin, int txPin, const Keypad *keypad);
		void initialize(CallbackPointer unlockedCallback);
		void update();
	};
}

#endif

