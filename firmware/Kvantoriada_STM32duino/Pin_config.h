#ifndef Pin_config_h
#define Pin_config_h

struct Pin_config
{
//////////    ENCODER /////////////////////////////////
//                               номер прерывания  пин(офиц номер)
    const uint8_t X1_encoder_pin = 3; // 3 (1)
    const uint8_t X2_encoder_pin = 2; // 2 (0)

    const uint8_t Y_encoder_pin = 18; // 18 (5)

    const uint8_t Z1_encoder_pin = 19; // 19 (4)
    const uint8_t Z2_encoder_pin = 4; // 4
    const uint8_t Z3_encoder_pin = 20; // 20 (3)
    const uint8_t Z4_encoder_pin = 21; // 21 (2)
///////////////////////////////////////////////////////
//////////    ENDSTOP /////////////////////////////////
    const uint8_t X1_endstop_pin = 27;
    const uint8_t X2_endstop_pin = 26;

    const uint8_t Y_endstop_pin = 24;

    const uint8_t Z1_endstop_pin = 25;
    const uint8_t Z2_endstop_pin = 28;
    const uint8_t Z3_endstop_pin = 22;
    const uint8_t Z4_endstop_pin = 23;
///////////////////////////////////////////////////////
};

#endif