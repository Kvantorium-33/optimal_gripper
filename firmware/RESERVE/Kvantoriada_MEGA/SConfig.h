#ifndef SCONFIG_H
#define SCONFIG_H
struct SConfig 
{
    const int Z1_id = 1;
    const int Z2_id = 2;
    const int Z3_id = 3;
    const int Z4_id = 4;

    const int X1_id = 5;
    const int X2_id = 6;
    
    const int Y_id = 7;

    const int valve_id = 8;
    const int Gripper_rotate_id = 9;
    const int Gripper_pol_id = 10;
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
    const int id_ar[10] = {Z1_id, Z2_id, Z3_id, Z4_id, X1_id, X2_id, Y_id,valve_id, Gripper_rotate_id, Gripper_pol_id};
    int32_t id_accel_ar[10] = {Z1_accel, Z2_accel, Z3_accel, Z4_accel, X1_accel, X2_accel, Y_accel, valve_accel, Gripper_rotate_accel, Gripper_pol_accel};
    int32_t id_speed_ar[10] = {Z1_speed, Z2_speed, Z3_speed, Z4_speed, X1_speed, X2_speed, Y_speed, valve_speed, Gripper_rotate_speed, Gripper_pol_speed};
//////////////////////////////////////////////////////////////////////////////////
    uint16_t model_number = 0;
    const int DXL_BAUDRATE = 57600;
    const char *log;
//////////////////////////////////////////////////////////////////////////////////
    const int COM_BAUDRATE = 9600;
//////////////////////////////////////////////////////////////////////////////////
#define ENDMODE_NORMAL false
#define ENDMODE_INTERR true    
};

#endif
