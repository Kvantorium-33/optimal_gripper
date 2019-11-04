#ifndef Axis_h
#define Axis_h
#include <Arduino.h>


class Axis
{
private:
    int _id = 0;
    int _encp = 0;
    int _endp = 0;
    unsigned int encoder_value = 0;

public:

    Axis();
    ~Axis();
    void Ainit(int _id_, int _encp_, int _endp_);
    boolean endstop_check();
    unsigned int encoder_counter();
};
#endif