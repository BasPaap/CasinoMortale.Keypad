#include "Keypad.h"

CasinoMortale::Keypad::Keypad()
{
}

void CasinoMortale::Keypad::initialize()
{
	Serial.println("Initializing keypad.");

	adafruitKeypad.begin();
}

void CasinoMortale::Keypad::update()
{
	adafruitKeypad.tick();

	while (adafruitKeypad.available()) {
		keypadEvent e = adafruitKeypad.read();
		Serial.print((char)e.bit.KEY);
		if (e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
		else if (e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
	}
}

