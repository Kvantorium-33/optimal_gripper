#ifndef PINOUT_CONFIG_H
#define PINOUT_CONFIG_H

struct Pinout_config
{
//////////    ENCODER /////////////////////////////////
    const int X1_encoder_pin = 16;
    const int X2_encoder_pin = 10;

    const int Y_encoder_pin = 8;

    const int Z1_encoder_pin = 6;
    const int Z2_encoder_pin = 4;
    const int Z3_encoder_pin = 2;
    const int Z4_encoder_pin = 0;
///////////////////////////////////////////////////////
//////////    ENDSTOP /////////////////////////////////
    const int X1_endstop_pin = 15;
    const int X2_endstop_pin = 13;

    const int Y_endstop_pin = 9;

    const int Z1_endstop_pin = 7;
    const int Z2_endstop_pin = 5;
    const int Z3_endstop_pin = 3;
    const int Z4_endstop_pin = 1;
///////////////////////////////////////////////////////



};



#endif