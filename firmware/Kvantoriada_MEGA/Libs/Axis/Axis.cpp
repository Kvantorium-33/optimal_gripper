#include <Arduino.h>
#include "Axis.h"


Axis::Axis()
{

};

void Axis::Ainit(int _id_, int _encp_, int _endp_)
{
    _id = _id_;
    _encp = _encp_;
    _endp = _endp_;

    pinMode(_encp, INPUT_PULLUP);
}