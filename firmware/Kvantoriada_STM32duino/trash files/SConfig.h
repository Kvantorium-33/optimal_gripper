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
    // int32_t Z1_accel = 100;
    // int32_t Z2_accel = 100;
    // int32_t Z3_accel = 100;
    // int32_t Z4_accel = 100;

    // int32_t X1_accel = 100;
    // int32_t X2_accel = 100;

    // int32_t Y_accel = 100;

    // int32_t valve_accel = 100;
    // int32_t Gripper_rotate_accel = 100;
    // int32_t Gripper_pol_accel = 100;
//////////////////////////////////////////////////////////////////////////////////    
    int32_t Z1_speed[3] = {1023, 100, 0};
    int32_t Z2_speed[3] = {1023, 100, 0};
    int32_t Z3_speed[3] = {1023, 100, 0};
    int32_t Z4_speed[3] = {1023, 100, 0};
    
    int32_t X1_speed[3] = {1023, 100, 0};
    int32_t X2_speed[3] = {1023, 100, 0};

    int32_t Y_speed[3] = {1023, 100, 0};

    int32_t valve_speed[3] = {1023, 100, 0};
    int32_t Gripper_rotate_speed[3] = {1023, 100, 0};
    int32_t Gripper_pol_speed[3] = {1023, 100, 0};
//////////////////////////////////////////////////////////////////////////////////    
    const int motor_count = 10;
    const uint8_t id_ar[10] = {Z1_id, Z2_id, Z3_id, Z4_id, X1_id, X2_id, Y_id,valve_id, Gripper_rotate_id, Gripper_pol_id};
    //int32_t id_accel_ar[10] = {Z1_accel, Z2_accel, Z3_accel, Z4_accel, X1_accel, X2_accel, Y_accel, valve_accel, Gripper_rotate_accel, Gripper_pol_accel};
    int32_t id_speed_ar[10] = {Z1_speed[1], Z2_speed[1], Z3_speed[1], Z4_speed[1], X1_speed[1], X2_speed[1], Y_speed[1], valve_speed[1], Gripper_rotate_speed[1], Gripper_pol_speed[1]};

    int grip_rot[2] = {100, 0};
    int grip_pol[2] = {100, 0};
    int valve_st[2] = {100, 0};
//////////////////////////////////////////////////////////////////////////////////
    uint16_t model_number = 0;
    const int dir_pin = 26;
    const int32_t DXL_BAUDRATE = 1000000;
    const char *log;
//////////////////////////////////////////////////////////////////////////////////
    const int32_t COM_BAUDRATE = 9600;
//////////////////////////////////////////////////////////////////////////////////
#define ENDMODE_NORMAL false
#define ENDMODE_INTERR true  
  
};

#endif
