#include "Keypad.h"

CasinoMortale::Keypad::Keypad()
{
}

void CasinoMortale::Keypad::initialize(CallbackPointer correctPinEnteredCallback, CallbackPointer wrongPinEnteredCallBack, CallbackPointer newPinSavedCallback)
{
	Serial.println("Initializing keypad.");

	this->correctPinEnteredCallback = correctPinEnteredCallback;
	this->wrongPinEnteredCallBack = wrongPinEnteredCallBack;
	this->newPinSavedCallback = newPinSavedCallback;

	adafruitKeypad.begin();
}

void CasinoMortale::Keypad::update()
{
	adafruitKeypad.tick();
	
	if ((strlen(currentlyEnteredPin) > 0 || strlen(pinToSet) > 0) &&
		millis() - lastKeyPressTime > keyPressTimeoutDuration)
	{
		Serial.println("Keypad timed out, resetting entered pin.");
		memset(currentlyEnteredPin, '\0', maxPinLength + 1);	// Completely clear the currently entered pin.
		memset(pinToSet, '\0', maxPinLength + 1);	// Completely clear the pin to set.
		numSequentialAsteriskKeyPresses = 0;
	}

	// If the pin buffers have been cleared, check if the asterisk is being pressed
	// so that we can determine if we need to be reading a new pin to set.
	if (strlen(currentlyEnteredPin) == 0 &&
		strlen(pinToSet) == 0 &&
		adafruitKeypad.justPressed('*'))
	{
		numSequentialAsteriskKeyPresses++;

		if (numSequentialAsteriskKeyPresses == numTimesToPressAsteriskKeyToSetNewPin)
		{
			Serial.println("Reading new pin to set.");
		}
	}
	
	bool isNewPinBeingSet = numSequentialAsteriskKeyPresses == numTimesToPressAsteriskKeyToSetNewPin;
	
	// If there is a value in pinToSet, check if the pound button is being pressed.
	// if so, we need to save the pin.
	if (isNewPinBeingSet &&
		strlen(pinToSet) > 0 &&
		adafruitKeypad.justPressed('#'))
	{
		Serial.print("Saving new pin ");
		Serial.print(pinToSet);
		Serial.println(" to memory.");		

		this->newPinSavedCallback();
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
				if (strlen(pinToSet) < maxPinLength)
				{
					pinToSet[strlen(pinToSet)] = pressedNumber;
					Serial.print("Currently entered pin to set: ");
					Serial.println(pinToSet);
				}
			}
			else
			{
				if (strlen(currentlyEnteredPin) < maxPinLength)
				{
					currentlyEnteredPin[strlen(currentlyEnteredPin)] = pressedNumber;
					Serial.print("Currently entered pin: ");
					Serial.println(currentlyEnteredPin);
				}
			}
		}

		lastKeyPressTime = millis();
	}

	delay(10);	
}

