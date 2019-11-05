#include <Arduino.h>
#include "Axis.h"

Axis::Axis()
{

};

int Axis::encoder_counter()
{
    _encoder_value++;
    return _encoder_value;
};

void Axis::Ainit(uint8_t _id_,uint8_t _endstop_pin_, uint8_t _encoder_pin_)
{
    _id = _id_;
    _encoder_pin = _encoder_pin_;
    _endstop_pin = _endstop_pin_;

    pinMode(_endstop_pin, INPUT_PULLUP);
    pinMode(_encoder_pin, INPUT_PULLUP);

    attachInterrupt(_encoder_pin, Axis::encoder_counter, RISING);
    
};



bool Axis::endstop_check()
{
    return digitalRead(_endstop_pin);
};

void Axis::reload()
{
    _encoder_value = 0;
};