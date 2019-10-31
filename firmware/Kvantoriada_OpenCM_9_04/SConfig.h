#ifndef SCONFIG_H
#define SCONFIG_H
struct SConfig 
{
    const uint8_t Z1_id = 1;
    const uint8_t Z2_id = 2;
    const uint8_t Z3_id = 3;
    const uint8_t Z4_id = 4;

    const uint8_t X1_id = 5;
    const uint8_t X2_id = 6;
    
    const uint8_t Y_id = 7;

    const uint8_t valve_id = 8;
    const uint8_t Gripper_rotate_id = 9;
    const uint8_t Gripper_pol_id = 10;
//////////////////////////////////////////////////////////////////////////////////
    int32_t Z1_accel = 100;
    int32_t Z2_accel = 100;
    int32_t Z3_accel = 100;
    int32_t Z4_accel = 100;

    int32_t X1_accel = 100;
    int32_t X2_accel = 100;

    int32_t Y_accel = 100;

    int32_t valve_accel = 100;
    int32_t Gripper_rotate_accel = 100;
    int32_t Gripper_pol_accel = 100;
//////////////////////////////////////////////////////////////////////////////////    
    int32_t Z1_speed = 100;
    int32_t Z2_speed = 100;
    int32_t Z3_speed = 100;
    int32_t Z4_speed = 100;
    int32_t X1_speed = 100;
    int32_t X2_speed = 100;

    int32_t Y_speed = 100;

    int32_t valve_speed = 100;
    int32_t Gripper_rotate_speed = 100;
    int32_t Gripper_pol_speed = 100;
//////////////////////////////////////////////////////////////////////////////////    
    const int motor_count = 10;
    const uint8_t id_ar[10] = {Z1_id, Z2_id, Z3_id, Z4_id, X1_id, X2_id, Y_id,valve_id, Gripper_rotate_id, Gripper_pol_id};
    int32_t id_accel_ar[10] = {Z1_accel, Z2_accel, Z3_accel, Z4_accel, X1_accel, X2_accel, Y_accel, valve_accel, Gripper_rotate_accel, Gripper_pol_accel};
    int32_t id_speed_ar[10] = {Z1_speed, Z2_speed, Z3_speed, Z4_speed, X1_speed, X2_speed, Y_speed, valve_speed, Gripper_rotate_speed, Gripper_pol_speed};
//////////////////////////////////////////////////////////////////////////////////
    uint16_t model_number = 0;
    const uint8_t DXL_BAUDRATE = 57600;
    const char *log;
//////////////////////////////////////////////////////////////////////////////////
    const uint8_t COM_BAUDRATE = 9600;
//////////////////////////////////////////////////////////////////////////////////
#define ENDMODE_NORMAL false
#define ENDMODE_INTERR true    
};

#endif
