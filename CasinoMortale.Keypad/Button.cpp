#include "Button.h"

namespace Bas
{
	Button::Button(int pin, unsigned long debounceDelay) : pin{ pin }, debounceDelay{ debounceDelay }, risingCallback{ NULL }, fallingCallback{ NULL }
	{
	}

	void Button::initialize(CallbackPointer fallingCallback)
	{
		this->initialize(fallingCallback, NULL);
	}

	void Button::initialize(CallbackPointer fallingCallback, CallbackPointer risingCallback)
	{
    Serial.print("Initializing button on pin ");
    Serial.println(this->pin);
		this->risingCallback = risingCallback;
		this->fallingCallback = fallingCallback;
		pinMode(this->pin, INPUT_PULLUP);
	}

	void Button::update()
	{
		int currentButtonState = digitalRead(this->pin);
		unsigned long now = millis();

		if (currentButtonState != this->lastDebouncedButtonState)
		{
			if (now - this->lastDebounceTime > this->debounceDelay)
			{
				// A debounced button change has occurred!
				this->lastDebounceTime = now;
				this->lastDebouncedButtonState = currentButtonState;
				this->debouncedState = currentButtonState;

				// Call the appropriate callback function
				if (this->risingCallback != NULL && currentButtonState == HIGH)
				{
					Serial.println("Button debounced on HIGH.");
					this->risingCallback();
				}

				if (currentButtonState == LOW)
				{
					Serial.println("Button debounced on LOW.");
					this->fallingCallback();
				}
			}
		}
	}
}
