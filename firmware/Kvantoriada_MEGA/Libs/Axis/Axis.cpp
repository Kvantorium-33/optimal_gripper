#include "Axis.h"
#include <Arduino.h>
Axis::Axis()
{

};

void Axis::Ainit(uint8_t _id_,uint8_t _endstop_pin_, uint8_t _encoder_pin_)
{
    _id = _id_;
    _encoder_pin = _encoder_pin_;
    _endstop_pin = _endstop_pin_;

    attachInterrupt(digitalPinToInterrupt(_encoder_pin_), encoder_counter, RISING);
    
};

uint8_t Axis::encoder_counter()
{
    _encoder_value++;
    return _encoder_value;
};

bool Axis::endstop_check()
{
    return bool(digitalRead(_encoder_pin));
};

void Axis::reload()
{
    _encoder_value = 0;
};