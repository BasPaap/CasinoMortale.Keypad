// 
// 
// 

#include "Feedback.h"

CasinoMortale::Feedback::Feedback(int redLedPin, int greenLedPin) : redLed { redLedPin }, greenLed { greenLedPin }
{
}

void CasinoMortale::Feedback::initialize()
{
	redLed.initialize();
	greenLed.initialize();
}

void CasinoMortale::Feedback::update()
{
	if (currentFeedbackDuration > 0 &&
		millis() - lastFeedbackTime > currentFeedbackDuration)
	{
		redLed.turnOff();
		greenLed.turnOff();
		currentFeedbackDuration = 0;
	}
}

void CasinoMortale::Feedback::playInitializedFeedback()
{
	redLed.turnOn();
	delay(100);
	greenLed.turnOn();
	delay(100);
	redLed.turnOff();
	delay(100);
	greenLed.turnOff();	
}

void CasinoMortale::Feedback::playUnlockedFeedback()
{
	redLed.turnOff();
	greenLed.turnOn();

	currentFeedbackDuration = 30000;
}

void CasinoMortale::Feedback::playWrongPinFeedback()
{
	redLed.turnOn();
	greenLed.turnOff();

	currentFeedbackDuration = 5000;
}

void CasinoMortale::Feedback::playNewPinSetFeedback()
{
	greenLed.turnOn();
	delay(500);
	greenLed.turnOff();
	delay(500);
	greenLed.turnOn();
	delay(500);
	greenLed.turnOff();
}
