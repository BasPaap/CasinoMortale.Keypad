// 
// 
// 

#include "Wiring.h"

CasinoMortale::Wiring::Wiring(const int dipSwitchPins[2], const int wirePins[3]) 
{
	for (size_t i = 0; i < sizeof(this->dipSwitchPins) / sizeof(this->dipSwitchPins[0]); i++)
	{
		this->dipSwitchPins[i] = dipSwitchPins[i];
	}

	for (size_t i = 0; i < numWirePins; i++)
	{
		this->wirePins[i] = wirePins[i];
	}
}

void CasinoMortale::Wiring::initialize(CallbackPointer overriddenCallback, CallbackPointer acceptingAlternativePinCodeCallback)
{
	Serial.println("Initializing wiring.");

	this->overriddenCallback = overriddenCallback;
	this->acceptingAlternativePinCodeCallback = acceptingAlternativePinCodeCallback;

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

	for (size_t i = 0; i < numWirePins; i++)
	{
		pinMode(wirePins[i], INPUT_PULLUP);
	}	
}

void CasinoMortale::Wiring::overrideSecurity()
{
	Serial.print("Security overridden on difficulty level ");
	Serial.print(difficultyLevel);
	Serial.println(".");

	isSecurityOverRidden = true;
	overriddenCallback();
}

void CasinoMortale::Wiring::update()
{
	const int firstPinIndex = 0;
	const int secondPinIndex = 1;
	const int thirdPinIndex = 2;
	if (!isSecurityOverRidden)
	{
		if (digitalRead(wirePins[firstPinIndex]) == requiredPinValue[firstPinIndex])
		{
			// First wire is overridden..
			if (difficultyLevel == 0)
			{
				overrideSecurity();
				return;
			}

			if (digitalRead(wirePins[secondPinIndex]) == requiredPinValue[secondPinIndex])
			{
				// First and second wire are overridden...
				if (difficultyLevel == 1)
				{
					overrideSecurity();
					return;
				}

				if (digitalRead(wirePins[thirdPinIndex]) == requiredPinValue[thirdPinIndex])
				{
					// First, second and third wire are overridden
					if (difficultyLevel == 2)
					{					
						overrideSecurity();

						return;
					}
					else if (difficultyLevel == 3)
					{
						Serial.println("Wiring set to accept alternative pin code on difficulty level 3.");
						isSecurityOverRidden = true;
						acceptingAlternativePinCodeCallback();
						return;
					}
				}
			}
		}
	}
}
