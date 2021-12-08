#include "Keypad.h"

CasinoMortale::Keypad::Keypad()
{
}

void CasinoMortale::Keypad::initialize(CallbackPointer correctPinCodeEnteredCallback, CallbackPointer wrongPinCodeEnteredCallBack, CallbackPointer newPinCodeSavedCallback)
{
	Serial.println("Initializing keypad.");

	this->correctPinCodeEnteredCallback = correctPinCodeEnteredCallback;
	this->wrongPinCodeEnteredCallBack = wrongPinCodeEnteredCallBack;
	this->newPinCodeSavedCallback = newPinCodeSavedCallback;

	adafruitKeypad.begin();
}

void CasinoMortale::Keypad::update()
{
	adafruitKeypad.tick();
	
	if ((strlen(currentlyEnteredPinCode) > 0 || strlen(pinCodeToSet) > 0) &&
		millis() - lastKeyPressTime > keyPressTimeoutDuration)
	{
		Serial.println("Keypad timed out, resetting entered pin code.");
		memset(currentlyEnteredPinCode, '\0', maxPinCodeLength + 1);	// Completely clear the currently entered pin code.
		memset(pinCodeToSet, '\0', maxPinCodeLength + 1);	// Completely clear the pin code to set.
		numSequentialAsteriskKeyPresses = 0;
	}

	// If the pin code buffers have been cleared, check if the asterisk is being pressed
	// so that we can determine if we need to be reading a new pin to set.
	if (strlen(currentlyEnteredPinCode) == 0 &&
		strlen(pinCodeToSet) == 0 &&
		adafruitKeypad.justPressed('*'))
	{
		numSequentialAsteriskKeyPresses++;

		if (numSequentialAsteriskKeyPresses == numTimesToPressAsteriskKeyToSetNewPinCode)
		{
			Serial.println("Reading new pin code to set.");
		}
	}
	
	bool isNewPinBeingSet = numSequentialAsteriskKeyPresses == numTimesToPressAsteriskKeyToSetNewPinCode;
	
	// If there is a value in pinCodeToSet, check if the pound button is being pressed.
	// if so, we need to save the pin code.
	if (isNewPinBeingSet &&
		strlen(pinCodeToSet) > 0 &&
		adafruitKeypad.justPressed('#'))
	{
		Serial.print("Saving new pin code");
		Serial.print(pinCodeToSet);
		Serial.println(" to memory.");		

		this->newPinCodeSavedCallback();
	}

	if (adafruitKeypad.justPressed('0') ||
		adafruitKeypad.justPressed('1') ||
		adafruitKeypad.justPressed('2') ||
		adafruitKeypad.justPressed('3') ||
		adafruitKeypad.justPressed('4') ||
		adafruitKeypad.justPressed('5') ||
		adafruitKeypad.justPressed('6') ||
		adafruitKeypad.justPressed('7') ||
		adafruitKeypad.justPressed('8') ||
		adafruitKeypad.justPressed('9'))
	{
		Serial.println("Key 0..9 pressed.");
				
		char pressedNumber = 0;
		while (adafruitKeypad.available()) {
			keypadEvent e = adafruitKeypad.read();
			
			if (e.bit.EVENT == KEY_JUST_PRESSED)
			{
				if ((char)e.bit.KEY != '*' && (char)e.bit.KEY != '#')
				{
					pressedNumber = e.bit.KEY;
					break;
				}				
			}
		}

		if (pressedNumber != 0)
		{
			if (isNewPinBeingSet)
			{
				if (strlen(pinCodeToSet) < maxPinCodeLength)
				{
					pinCodeToSet[strlen(pinCodeToSet)] = pressedNumber;
					Serial.print("Currently entered pin code to set: ");
					Serial.println(pinCodeToSet);
				}
			}
			else
			{
				if (strlen(currentlyEnteredPinCode) < maxPinCodeLength)
				{
					currentlyEnteredPinCode[strlen(currentlyEnteredPinCode)] = pressedNumber;
					Serial.print("Currently entered pin code: ");
					Serial.println(currentlyEnteredPinCode);
				}
			}
		}

		lastKeyPressTime = millis();
	}

	delay(10);	
}

