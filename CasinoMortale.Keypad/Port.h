// Port.h

#ifndef _PORT_h
#define _PORT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace CasinoMortale
{
	class Port
	{
		int rxPin;
		int txPin;
		bool isCommunicating;

	public:
		Port(int rxPin, int txPin);
		void initialize();
		void update();
	};
}

#endif

