// Feedback.h

#ifndef _FEEDBACK_h
#define _FEEDBACK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Led.h"

namespace CasinoMortale
{
	class Feedback
	{		
		Bas::Led redLed;
		Bas::Led greenLed;

	public:
		Feedback(int redLedPin, int greenLedPin);
		void initialize();
		void update();
		void playInitializedFeedback();
		void playUnlockedFeedback();
		void playWrongPinFeedback();
		void playNewPinSetFeedback();
	};
}


#endif
