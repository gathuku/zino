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

 Created by: Saleem Hadad
 Date: 30/12/2017
 Github: https://github.com/saleem-hadad/zino
*/

#include "Pin.h"

Pin::Pin(char pin): _pin(pin)
{
    if(pin >= 0 && pin <= 7)
    {
        this->_pin  = pin;
        this->_port = Port::PortD;
    }
    else if(pin >= 8 && pin <= 13)
    {
        this->_pin  = pin - 8;
        this->_port = Port::PortB;
    }
}

Pin::Pin(Port port, char pin): _port(port), _pin(pin)
{
    this->_port = port;
    this->_pin  = pin;
}

Port Pin::port()
{
    return this->_port;
}

char Pin::pin()
{
    return this->_pin;
}
