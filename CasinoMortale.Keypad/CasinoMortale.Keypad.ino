/*
 Name:		CasinoMortale.ino
 Created:	12/7/2021 10:04:58 PM
 Author:	baspa
*/

// the setup function runs once when you press reset or power the board

#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Adafruit_Keypad_Ringbuffer.h>
#include <Adafruit_Keypad.h>

#include "Keypad.h"
#include "Button.h"
#include "Feedback.h"
#include "Wiring.h"
#include "Port.h"

const int greenLedPin = A1;
const int redLedPin = A0;
const int requestNewPinCodeButtonPin = A4;
const unsigned long debounceDelay = 50;
const int dipSwitchPins[] = { A2, A3 };
const int wirePins[] = { 11, 12, A5 };
const int portRxPin = A7;
const int portTxPin = 10;
const int speakerPin = 9;

CasinoMortale::Feedback feedback { redLedPin, greenLedPin, speakerPin };
CasinoMortale::Keypad keypad;
CasinoMortale::Wiring wiring{ wirePins };
CasinoMortale::Port port { portRxPin, portTxPin, &keypad };
Bas::Button requestNewPinCodeButton { requestNewPinCodeButtonPin, debounceDelay };

bool isLocked = true;
int difficultyLevel = 0;

void setup() {
	Serial.begin(9600);
	
	SetDifficultyLevel();

	feedback.initialize();
	keypad.initialize(onUnlocked, onWrongPinCodeEntered, onNewPinCodeSaved);	
	requestNewPinCodeButton.initialize(onRequestNewPinCodeButtonPressed);
	wiring.initialize(onSecurityOverridden, onAcceptingAlternativePinCode, difficultyLevel);
	port.initialize(onUnlocked, difficultyLevel);
	feedback.playInitializedFeedback();	
}

int SetDifficultyLevel()
{
	for (size_t i = 0; i < sizeof(dipSwitchPins) / sizeof(dipSwitchPins[0]); i++)
	{
		pinMode(dipSwitchPins[i], INPUT_PULLUP);
		if (digitalRead(dipSwitchPins[i]) == LOW)
		{
			difficultyLevel += pow(2, i);
		}
	}

	Serial.print("Difficulty level set to ");
	Serial.print(difficultyLevel);
	Serial.println(".");
}

// the loop function runs over and over again until power down or reset
void loop() {
	requestNewPinCodeButton.update();
	keypad.update();	 
	wiring.update();
	feedback.update();
	port.update();
}

void onSecurityOverridden()
{
	isLocked = false;
	feedback.playOverriddenFeedback();
}

void onAcceptingAlternativePinCode()
{
	keypad.acceptAlternativePinCode();
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
