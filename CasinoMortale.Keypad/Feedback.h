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

		unsigned long lastFeedbackTime;
		unsigned long currentFeedbackDuration;
		int speakerPin;
		void playBondTheme();
		void playSuccessSound();
		void playErrorSound();
		void playNotes(int* notes, int* noteDurations, int size);
	public:
		Feedback(int redLedPin, int greenLedPin, int speakerPin);
		void initialize();
		void update();
		void playInitializedFeedback();
		void playUnlockedFeedback();
		void playWrongPinCodeFeedback();
		void playNewPinCodeSetFeedback();
		void playOverriddenFeedback();		
	};
}


#endif

