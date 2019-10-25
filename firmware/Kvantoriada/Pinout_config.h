#ifndef PINOUT_CONFIG_H
#define PINOUT_CONFIG_H

struct Pinout_config
{
//////////    ENCODER /////////////////////////////////
    const uint8_t X1_encoder_pin = 16;
    const uint8_t X2_encoder_pin = 10;

    const uint8_t Y_encoder_pin = 8;

    const uint8_t Z1_encoder_pin = 6;
    const uint8_t Z2_encoder_pin = 4;
    const uint8_t Z3_encoder_pin = 2;
    const uint8_t Z4_encoder_pin = 0;
///////////////////////////////////////////////////////
//////////    ENDSTOP /////////////////////////////////
    const uint8_t X1_endstop_pin = 15;
    const uint8_t X2_endstop_pin = 13;

    const uint8_t Y_endstop_pin = 9;

    const uint8_t Z1_endstop_pin = 7;
    const uint8_t Z2_endstop_pin = 5;
    const uint8_t Z3_endstop_pin = 3;
    const uint8_t Z4_endstop_pin = 1;
///////////////////////////////////////////////////////



};



#endif