#include "Axis.h"

Axis::Axis()
{

};

void Axis::Ainit(uint8_t _id_,uint8_t _endstop_pin_, uint8_t _encoder_pin_)
{
    _id = _id_;
    _encoder_pin = _encoder_pin_;
    _endstop_pin = _endstop_pin_;

    pinMode(_endstop_pin, INPUT_PULLDOWN);
    pinMode(_encoder_pin, INPUT_PULLDOWN);

    attachInterrupt(_encoder_pin, encoder_counter, RISING);
    
};

uint8_t Axis::encoder_counter()
{
    _encoder_value++;
    return _encoder_value;
};

void Axis::endstop_mode(bool mode)
{   _endstop_mode == mode;
    if (mode == INTERR)
        attachInterrupt(_endstop_pin, endstop_check,CHANGE);
};

bool Axis::endstop_check()
{
    if (_endstop_mode == INTERR)
        _endstop_status = !_endstop_status;
    if (_endstop_status == NORMAL)
        _endstop_status = digitalRead(_endstop_pin);
};

void Axis::reload()
{
    _encoder_value = 0;
};