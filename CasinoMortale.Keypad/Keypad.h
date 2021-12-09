// Keypad.h

#pragma once

#ifndef _KEYPAD_h
#define _KEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Adafruit_Keypad.h"

// define your specific keypad here via PID
#define KEYPAD_PID3845
// define your pins here
// can ignore ones that don't apply
#define R1    7
#define R2    2
#define R3    3
#define R4    5
#define C1    6
#define C2    8
#define C3    4
#define C4    11 // Not used

// leave this import after the above configuration

namespace CasinoMortale
{
	class Keypad
	{
		using CallbackPointer = void(*)();
		static const int maxPinCodeLength = 6;		
		const unsigned long keyPressTimeoutDuration = 5000;
		static const byte ROWS = 4; // rows
		static const byte COLS = 3; // columns
		const int savedPinCodeLengthAddress = 0;
		//// define the symbols on the buttons of the keypads
		char keys[ROWS][COLS] = {
			{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'} };
		byte rowPins[ROWS] = { R1, R2, R3,
							  R4 };         // connect to the row pinouts of the keypad
		byte colPins[COLS] = { C1, C2, C3 }; // connect to the column pinouts of the
										   // keypad
				
		unsigned long lastKeyPressTime;
		char savedPinCode[maxPinCodeLength + 1];
		char currentlyEnteredPinCode[maxPinCodeLength + 1];
		char newPinCode[maxPinCodeLength + 1];
		Adafruit_Keypad adafruitKeypad = Adafruit_Keypad{ makeKeymap(keys), rowPins, colPins, ROWS, COLS };
		CallbackPointer correctPinCodeEnteredCallback;
		CallbackPointer wrongPinCodeEnteredCallBack;
		CallbackPointer newPinCodeSavedCallback;
		bool isNewPinCodeBeingSet;
		const char alternativePinCode[5] = "0000";
		bool isAcceptingAlternativePinCode;

		void clearAllInput();
		void loadPinCode();
		void savePinCode(char pinCode[]);

	public:
		Keypad();
		void initialize(CallbackPointer correctPinCodeEnteredCallback, CallbackPointer wrongPinCodeEnteredCallBack, CallbackPointer newPinCodeSavedCallback);
		void update();
		void onRequestedNewPinCodeEntry();
		void acceptAlternativePinCode();
	};
}


#endif

