/*
 Name:		CasinoMortale.ino
 Created:	12/7/2021 10:04:58 PM
 Author:	baspa
*/

// the setup function runs once when you press reset or power the board
#include <Adafruit_Keypad_Ringbuffer.h>
#include <Adafruit_Keypad.h>

#include "Keypad.h"
#include "Led.h"

const int greenLedPin = A0;
const int redLedPin = A1;

Bas::Led redLed{ redLedPin };
Bas::Led greenLed{ greenLedPin };
CasinoMortale::Keypad keypad;

bool isLocked = true;

void setup() {
	Serial.begin(9600);

	greenLed.initialize();
	redLed.initialize();	
	keypad.initialize();

	redLed.turnOn();
}

// the loop function runs over and over again until power down or reset
void loop() {
	keypad.update();	 
}
