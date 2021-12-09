// 
// 
// 

#include "Feedback.h"

CasinoMortale::Feedback::Feedback(int redLedPin, int greenLedPin) : redLed { redLedPin }, greenLed { greenLedPin }
{
}

void CasinoMortale::Feedback::initialize()
{
	Serial.println("Initializing feedback.");
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
	lastFeedbackTime = millis();
}

void CasinoMortale::Feedback::playWrongPinCodeFeedback()
{
	redLed.turnOn();
	greenLed.turnOff();

	currentFeedbackDuration = 5000;
	lastFeedbackTime = millis();
}

void CasinoMortale::Feedback::playOverriddenFeedback()
{
	for (size_t i = 0; i < 2; i++)
	{
		redLed.turnOn();
		delay(100);
		greenLed.turnOn();
		delay(100);
		redLed.turnOff();
		delay(100);
		redLed.turnOn();
		delay(100);
		greenLed.turnOff();
		redLed.turnOff();
		/*delay(100);
		greenLed.turnOn();
		redLed.turnOff();
		delay(100);
		greenLed.turnOff();*/
		delay(100);
	}

	greenLed.turnOn();
}

void CasinoMortale::Feedback::playNewPinCodeSetFeedback()
{
	greenLed.turnOn();
	delay(500);
	greenLed.turnOff();
	delay(500);
	greenLed.turnOn();
	delay(500);
	greenLed.turnOff();
}
