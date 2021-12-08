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
#include "Button.h"

const int greenLedPin = A0;
const int redLedPin = A1;
const int requestNewPinCodeButtonPin = A4;
const unsigned long debounceDelay = 50;

CasinoMortale::Feedback feedback { redLedPin, greenLedPin };
CasinoMortale::Keypad keypad;
Bas::Button requestNewPinCodeButton { requestNewPinCodeButtonPin, debounceDelay };

bool isLocked = true;

void setup() {
	Serial.begin(9600);

	feedback.initialize();
	keypad.initialize(onUnlocked, onWrongPinCodeEntered, onNewPinCodeSaved);	
	requestNewPinCodeButton.initialize(onRequestNewPinCodeButtonPressed);
	feedback.playInitializedFeedback();
}

// the loop function runs over and over again until power down or reset
void loop() {
	requestNewPinCodeButton.update();
	keypad.update();	 
	feedback.update();
}

void onUnlocked()
{
	isLocked = false;
	feedback.playUnlockedFeedback();
}

void onRequestNewPinCodeButtonPressed()
{
	Serial.println("New pin code button pressed.");
	keypad.onRequestedNewPinCodeEntry();
}

void onWrongPinCodeEntered()
{
	isLocked = true;
	feedback.playWrongPinCodeFeedback();
}

void onNewPinCodeSaved()
{
	feedback.playNewPinCodeSetFeedback();
}
