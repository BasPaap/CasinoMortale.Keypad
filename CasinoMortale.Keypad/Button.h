// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
namespace Bas
{
	/// <summary>
	/// Encapsulate a button connected to a pull-up resistor. If the button is pressed or released (and any bouncing is filtered out), a callback is called.
	/// </summary>
	class Button
	{
		using CallbackPointer = void(*)();
		int pin;
		int lastDebouncedButtonState = HIGH;
		unsigned long lastDebounceTime;
		unsigned long debounceDelay;
		CallbackPointer risingCallback;
		CallbackPointer fallingCallback;
		int debouncedState;

	public:
		/// <summary>
		/// Constructs the Button object.
		/// </summary>
		/// <param name="pin">The pin the button is connected to.</param>
		/// <param name="debounceDelay">The delay (in millis) to use for filtering any bouncing.</param>
		/// <returns></returns>
		Button(int pin, unsigned long debounceDelay);

		/// <summary>
		/// Tell the button which callback to call when the signal falls (in other words, when the button is pressed).
		/// </summary>
		/// <param name="fallingCallback">The callback to call when the button is pressed.</param>
		void initialize(CallbackPointer fallingCallback);

		/// <summary>
		/// Tell the button which callback to call when the signal falls (when the button is pressed) or rises (when the button is released).
		/// </summary>
		/// <param name="fallingCallback">The callback to call when the button is pressed.</param>
		/// <param name="risingCallback">The callback to call when the button is released.</param>
		void initialize(CallbackPointer fallingCallback, CallbackPointer risingCallback);

		/// <summary>
		/// Updates the Button state. This method should be called once per loop.
		/// </summary>
		void update();
	};
}

#endif

