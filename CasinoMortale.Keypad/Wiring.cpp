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

	for (size_t i = 0; i < sizeof(this->wirePins) / sizeof(this->wirePins[0]); i++)
	{
		this->wirePins[i] = wirePins[i];
	}
}

void CasinoMortale::Wiring::initialize()
{
	Serial.println("Initializing wiring.");

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

	for (size_t i = 0; i < sizeof(wirePins) / sizeof(wirePins[0]); i++)
	{
		pinMode(wirePins[i], INPUT_PULLUP);
	}	
}

void CasinoMortale::Wiring::update()
{
}
