#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

namespace Bas
{
	class Led
	{
		int pin;
	public:
		Led(int pin);
		void initialize();
		void turnOn();
		void turnOff();
	};
}
