/*
 .----------------.  .----------------.  .-----------------. .----------------.
| .--------------. || .--------------. || .--------------. || .--------------. |
| |   ________   | || |     _____    | || | ____  _____  | || |     ____     | |
| |  |  __   _|  | || |    |_   _|   | || ||_   \|_   _| | || |   .'    `.   | |
| |  |_/  / /    | || |      | |     | || |  |   \ | |   | || |  /  .--.  \  | |
| |     .'.' _   | || |      | |     | || |  | |\ \| |   | || |  | |    | |  | |
| |   _/ /__/ |  | || |     _| |_    | || | _| |_\   |_  | || |  \  `--'  /  | |
| |  |________|  | || |    |_____|   | || ||_____|\____| | || |   `.____.'   | |
| |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'

 Github: https://github.com/saleem-hadad/zino
*/

#include "Button.h"
#include <Arduino.h>
#include "GPIO.h"

Button::Button()
{
    //
}

void Button::init(Pin pin, char debouncePeriod, bool defaultHigh, bool withPullUp)
{
    this->_pin = &pin;
    this->_debouncePeriod = debouncePeriod;
    this->_defaultHigh = defaultHigh;
    this->_initialized = true;

    if (withPullUp)
    {
        GPIO::setup(pin, InputWithPullUp);
        return;
    }

    GPIO::setup(pin, Input);
}

void Button::refresh()
{
    if(! this->_initialized) { return; }

    if(this->_waiting)
    {
        if(millis() - this->_pressed_time >= this->_debouncePeriod)
        {
            this->_waiting = false;
            bool current = GPIO::read(*this->_pin);

            if(current) {
                if(this->pressed) (*this->pressed)();
            }

            this->_previous = current;
        }
    }
    else
    {
        bool current = GPIO::read(*this->_pin);
        if(current && ! this->_previous)
        {
            this->_pressed_time = millis();
            this->_waiting = true;
        }
        this->_previous = current;
    }
}
