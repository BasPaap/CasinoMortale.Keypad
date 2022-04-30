// Wiring.h

#ifndef _WIRING_h
#define _WIRING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace CasinoMortale
{
	class Wiring
	{
		static const int numWirePins = 3;
		using CallbackPointer = void(*)();
		int wirePins[numWirePins];	
		int requiredPinValue[numWirePins] = { HIGH, HIGH, LOW };
		int difficultyLevel;
		CallbackPointer overriddenCallback;
		CallbackPointer acceptingAlternativePinCodeCallback;
		bool isSecurityOverRidden;
		
		void overrideSecurity();

	public:
		Wiring(const int wirePins[3]);
		void initialize(CallbackPointer correctPinCodeEnteredCallback, CallbackPointer acceptingAlternativePinCodeCallback, int difficultyLevel);
		void update();
	};
}

#endif

