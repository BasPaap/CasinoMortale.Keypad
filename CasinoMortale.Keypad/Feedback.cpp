// 
// 
// 

#include "Feedback.h"
#include "Pitches.h"

CasinoMortale::Feedback::Feedback(int redLedPin, int greenLedPin, int speakerPin) : redLed { redLedPin }, greenLed { greenLedPin }, speakerPin { speakerPin }
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

	playSuccessSound();
}

void CasinoMortale::Feedback::playWrongPinCodeFeedback()
{
	redLed.turnOn();
	greenLed.turnOff();

	currentFeedbackDuration = 5000;
	lastFeedbackTime = millis();

	playErrorSound();
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

	playBondTheme();
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

void CasinoMortale::Feedback::playBondTheme()
{
	int melody[] = {
		NOTE_E5, NOTE_G5, 0, NOTE_DS6, NOTE_D6
	};

	// note durations: 4 = quarter note, 8 = eighth note, etc.:
	int noteDurations[] = {

	  4, 8, 16, 8, 2
	};

	for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) 
	{

		// to calculate the note duration, take one second divided by the note type.

		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

		int noteDuration = 1000 / noteDurations[thisNote];

		tone(speakerPin, melody[thisNote], noteDuration);

		// to distinguish the notes, set a minimum time between them.

		// the note's duration + 30% seems to work well:

		int pauseBetweenNotes = noteDuration * 1.30;

		delay(pauseBetweenNotes);

		// stop the tone playing:

		noTone(speakerPin);
	}
}

void CasinoMortale::Feedback::playSuccessSound()
{
	int melody[] = {
		NOTE_E5, NOTE_E6
	};

	// note durations: 4 = quarter note, 8 = eighth note, etc.:
	int noteDurations[] = {

	  8, 8
	};

	for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++)
	{

		// to calculate the note duration, take one second divided by the note type.

		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

		int noteDuration = 1000 / noteDurations[thisNote];

		tone(speakerPin, melody[thisNote], noteDuration);

		// to distinguish the notes, set a minimum time between them.

		// the note's duration + 30% seems to work well:

		int pauseBetweenNotes = noteDuration * 1.30;

		delay(pauseBetweenNotes);

		// stop the tone playing:

		noTone(speakerPin);
	}
}

void CasinoMortale::Feedback::playErrorSound()
{
	int melody[] = {
		NOTE_D2
	};

	// note durations: 4 = quarter note, 8 = eighth note, etc.:
	int noteDurations[] = {

	  1
	};

	for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++)
	{

		// to calculate the note duration, take one second divided by the note type.

		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

		int noteDuration = 1000 / noteDurations[thisNote];

		tone(speakerPin, melody[thisNote], noteDuration);

		// to distinguish the notes, set a minimum time between them.

		// the note's duration + 30% seems to work well:

		int pauseBetweenNotes = noteDuration * 1.30;

		delay(pauseBetweenNotes);

		// stop the tone playing:

		noTone(speakerPin);
	}
}