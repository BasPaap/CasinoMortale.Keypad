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
		int dipSwitchPins[2];
		int wirePins[3];
		int difficultyLevel;
		
	public:
		Wiring(const int dipSwitchPins[2], const int wirePins[3]);
		void initialize();
		void update();
	};
}

#endif

