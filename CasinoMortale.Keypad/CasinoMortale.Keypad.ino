/*
 Name:		CasinoMortale.ino
 Created:	12/7/2021 10:04:58 PM
 Author:	baspa
*/

// the setup function runs once when you press reset or power the board
#include "Feedback.h"
#include <Adafruit_Keypad_Ringbuffer.h>
#include <Adafruit_Keypad.h>

#include "Keypad.h"


const int greenLedPin = A0;
const int redLedPin = A1;

CasinoMortale::Feedback feedback { redLedPin, greenLedPin };
CasinoMortale::Keypad keypad;

bool isLocked = true;

void setup() {
	Serial.begin(9600);

	feedback.initialize();
	keypad.initialize(onCorrectPinEntered, onWrongPinEntered, onNewPinSaved);	

	feedback.playInitializedFeedback();
}

// the loop function runs over and over again until power down or reset
void loop() {
	keypad.update();	 
	feedback.update();
}

void onCorrectPinEntered()
{
	isLocked = false;
	feedback.playUnlockedFeedback();
}

void onWrongPinEntered()
{
	isLocked = true;
	feedback.playWrongPinFeedback();
}

void onNewPinSaved()
{
	feedback.playNewPinSetFeedback();
}
