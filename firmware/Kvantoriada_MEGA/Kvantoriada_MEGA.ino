#if ! ( defined __AVR_ATmega2560__ || defined __AVR_ATmega1280__ || defined __AVR_ATmega1281__ || defined __AVR_ATmega2561__ || defined __AVR_ATmega640__ )
#error "This sketch only works on chips in the ATmega2560 family."
#endif
//#define COM Serial2                                                // BLUETOOTH
#define COM Serial                                                   // USB
////////////////// ПОДКЛЮЧЕНИЕ РАБОЧИХ БИБЛИОТЕК ///////////////////////
#include <Axis.h>                                                   // БИБЛИОТЕКА ОСЕЙ 
#include <Workspace.h>                                              // БИБЛИОТЕКА РАБОЧЕГО ПРОСТРАНСТВА
#include <Mathematics.h>                                            // БИБЛИОТЕКА МАТЕМАТИКИ  
#include <DynamixelSerial3.h>
////////////////// ПОДКЛЮЧЕНИЕ БИБЛИОТЕК ПАРАМЕТРОВ И ДАННЫХ ///////////
#include "Pinout_config.h"                                          // ПАРАМЕТРЫ ПИНОВ
#include "SConfig.h"                                                 // ОБЫЧНЫЕ ПАРАМЕТРЫ 
#include "WS_config.h"                                              // ПАРАМЕТРЫ РАБОЧЕГО ПРОСТРАНСТВА
/////////////////// КОНСТАНТЫ ДЛЯ ОБРАЩЕНИЯ К МАССИВАМ /////////////////
#define X_ 0                                                        // КОНСТАНТА ОБРАЩЕНИЯ К ЯЧЕКАМ СО ЗНАЧЕНИЯМИ ДЛЯ ОСИ Х
#define Y_ 1                                                        // КОНСТАНТА ОБРАЩЕНИЯ К ЯЧЕКАМ СО ЗНАЧЕНИЯМИ ДЛЯ ОСИ Y
#define Z_ 2                                                        // КОНСТАНТА ОБРАЩЕНИЯ К ЯЧЕКАМ СО ЗНАЧЕНИЯМИ ДЛЯ ОСИ Z
                                                                    //
#define move_up 1                                                   // ВПЕРЕД / ВВЕРХ
#define move_stop 0                                                 // СТОП   / СТОП
#define move_down -1                                                // НАЗАД  / ВНИЗ
                                                                    //
#define Z1_ar_cell 0                                                // ЯЧЕЙКА  ОСИ Z1
#define Z2_ar_cell 1                                                // ЯЧЕЙКА  ОСИ Z2
#define Z3_ar_cell 2                                                // ЯЧЕЙКА  ОСИ Z3
#define Z4_ar_cell 3                                                // ЯЧЕЙКА  ОСИ Z4
                                                                    // 
#define X1_ar_cell 4                                                // ЯЧЕЙКА  ОСИ X1
#define X2_ar_cell 5                                                // ЯЧЕЙКА  ОСИ X2
                                                                    // 
#define Y_ar_cell 6                                                 // ЯЧЕЙКА  ОСИ Y 
                                                                    // 
#define valve_ar_cell 7                                             // ЯЧЕЙКА  КЛАПАНА
                                                                    // 
#define Grip_rot_ar_cell 8                                          // ЯЧЕЙКА ПОВОРОТА ЗАХВАТА
#define Grip_pol_ar_cell 9                                          // ЯЧЕЙКА ПОЛОЖЕНИЯ ЗАХВАТА(ОТКРЫТИЕ - ЗАКРЫТИЕ)
                                                                    //
#define All 3                                                       // ЯЧЕЙКА ВСЕ
                                                                    //
#define ON true                                                     //
#define OFF false                                                   //
#define LEFT false
#define RIGHT true
                                                                    //
#define MAX_ 0                                                      // ЯЧЕЙКА МАКСИМАЛЬНОГО ПОЛОЖЕНИЯ / ПОВОРОТА / СКОРОСТИ
#define MID_ 1                                                      // ЯЧЕЙКА СРЕДНЕГО(ТЕКУЩЕГО) ПОЛОЖЕНИЯ / ПОВОРОТА  / СКОРОСТИ        
#define MIN_ 2                                                      // ЯЧЕЙКА МИНИМАЛЬНОГО ПОЛОЖЕНИЯ / ПОВОРОТА  / СКОРОСТИ
////////////////// ОБЪЯВЛЕНИЕ РАБОЧИХ ОБЪЕКТОВ /////////////////////////
Axis X1;                                                            //  ОБЪЕКТ ОСЬ X1
Axis X2;                                                            //  OБЪЕКТ ОСЬ X2
                                                                    //  
Axis Y;                                                             //  ОБЪЕКТ ОСЬ Y
                                                                    //   
Axis Z1;                                                            //  ОБЪЕКТ ОСЬ Z1
Axis Z2;                                                            //  ОБЪЕКТ ОСЬ Z2
Axis Z3;                                                            //  ОБЪЕКТ ОСЬ Z3
Axis Z4;                                                            //  ОБЪЕКТ ОСЬ Z4
                                                                    //  
Workspace WS;                                                       // ОБЪЕКТ РАБОЧЕГО ПРОСТРАНСТВА 
                                                                    //
                                                                    //
Mathematics Math;                                                   // ОБЪЕКТ МАТЕМАТИКИ
//////////////// ОБЪЯВЛЕНИЕ ОБЪЕКТОВ ДЛЯ БИБЛИОТЕК ДАННЫХ И ПАРАМЕТРОВ /
Pinout_config PC;                                                   // ОБЪЕКТ КОНФИГА ПИНОВ
SConfig Conf;                                                       // ОБЪЕКТ БАЗОВОГО КОНФИГА
//////////////// ОБЪЯВЛЕНИЕ МАССИВОВ ПОЗИЦИИ ///////////////////////////
int lastPos[3] = {0, 0, 0}; // X Y Z                                //
int nextPos[3] = {0, 0, 0}; // X Y Z                                //
void setup()                                                        //
{                                                                   //
    com_init();                                                     // ИНИЦИАЛИЗАЦИЯ ПОСЛЕДОВАТЕЛЬНО ПОРТА 
    //////////////////////////    X1    ////////////////////////////////
    X1.Ainit(Conf.X1_id, PC.X1_endstop_pin, PC.X1_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Х1 

    //////////////////////////    X2    ////////////////////////////////
    X2.Ainit(Conf.X2_id, PC.X2_endstop_pin, PC.X2_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Х2

    //////////////////////////    Y    /////////////////////////////////
    Y.Ainit(Conf.Y_id, PC.Y_endstop_pin, PC.Y_encoder_pin);         // ИНИЦИАЛИЗАЦИ ОСИ Y

    //////////////////////////    Z1    ////////////////////////////////
    Z1.Ainit(Conf.Z1_id, PC.Z1_endstop_pin, PC.Z1_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z1 

    //////////////////////////    Z2    ////////////////////////////////
    Z2.Ainit(Conf.Z2_id, PC.Z2_endstop_pin, PC.Z2_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z2

    //////////////////////////    Z3    ////////////////////////////////
    Z3.Ainit(Conf.Z3_id, PC.Z3_endstop_pin, PC.Z3_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z3

    //////////////////////////    Z4    ////////////////////////////////
    Z4.Ainit(Conf.Z4_id, PC.Z4_endstop_pin, PC.Z4_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z4 

    ///////////////////////// ПОДГОТОВКА РАБОЧЕГО ПРОСТРАНСТВА /////////
    WS.set_ws_size(ws_Size[X_], ws_Size[Y_], ws_Size[Z_]);          // УСТАНОВКА  РАЗМЕРОВ РАБОЧЕГО ПРОСТРАНСТВА (формат XYZ) 
    WS.set_cell_size(cell_Size[X_], cell_Size[Y_], cell_Size[Z_]);  // УСТАНОВКА РАЗМЕРОВ ЯЧЕЙКА (формат XYZ)
    ////////////////////////////////////////////////////////////////////
    Math.setWheelDeametr(Wheel_deametr);                            // УСТАНОВКА ДИАМЕТРА КОЛЕСА ЭНКОДЕРА
    Math.setWheelTiks(Wheel_ticks);                                 // УСТАНОВКА КОЛИЧЕСТВА ТИКОВ НА ОБОРОТ КОЛЕСА ЭНКОДЕРА
    Math.putWSs(ws_Size[X_], ws_Size[Y_], ws_Size[Z_]);             // УСТАНОВКА  РАЗМЕРОВ РАБОЧЕГО ПРОСТРАНСТВА ДЛЯ МАТЕМАТИКИ (формат XYZ) 
    Math.puCells(cell_Size[X_], cell_Size[Y_], cell_Size[Z_]);      // УСТАНОВКА РАЗМЕРОВ ЯЧЕЙКА ДЛЯ МАТЕМАТИКИ (формат XYZ)
    ///////////////////////// ПОДГОТОВКА МОТОРОВ ///////////////////////
    Dynamixel.begin(Conf.DXL_BAUDRATE, Conf.dir_pin, Conf.dir_pin);
    motor_init();
    motor_blink();
}

///////////////////////////////////     КОММУНИКАЦИИ ///////////////////////////////////////////////
void com_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ ПОСЛЕДОВАТЕЛЬНО ПОРТА
{   
    COM.begin(Conf.COM_BAUDRATE);
    COM.println("Hello"); 
}
///////////////////////////////////     МОТОРЫ       ///////////////////////////////////////////////
void motor_init()
{   int attemps = 0;
    for (int i = 0; i < Conf.motor_count; i++)
    {   
        Dynamixel.ledStatus(Conf.id_ar[i - 1], OFF);
        Dynamixel.ledStatus(Conf.id_ar[i], ON);
        while (!Dynamixel.ping(Conf.id_ar[i]) || attemps != 3)
            attemps++;
        delay(500);
    }
}

void motor_blink()
{
    for (int i = 0; i < Conf.motor_count; i++)
    {   
        Dynamixel.ledStatus(Conf.id_ar[i - 1], OFF);
        Dynamixel.ledStatus(Conf.id_ar[i], ON);
        delay(500);
    }
}

void move_X (int dirX = move_stop, bool on1 = OFF, bool on2 = OFF)
{
    //true - RIGHT
    // false - LEFT
    switch(dirX)
    {
        case move_up:

            if (on1 == ON)
                Dynamixel.turn(Conf.id_ar[X1_ar_cell], LEFT, Conf.id_speed_ar[X1_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[X1_ar_cell], LEFT, 0);

             if (on2 == ON)
                Dynamixel.turn(Conf.id_ar[X2_ar_cell], RIGTH, Conf.id_speed_ar[X1_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[X2_ar_cell], RIGHT, 0);

        break;

        case move_stop:

             Dynamixel.turn(Conf.id_ar[X2_ar_cell], RIGHT, 0);
             Dynamixel.turn(Conf.id_ar[X1_ar_cell], LEFT, 0);

        break;

        case move_down:

            if (on1 == ON)
                Dynamixel.turn(Conf.id_ar[X1_ar_cell], RIGHT, Conf.id_speed_ar[X1_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[X1_ar_cell], RIGHT, 0);

             if (on2 == ON)
                Dynamixel.turn(Conf.id_ar[X2_ar_cell], LEFT, Conf.id_speed_ar[X1_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[X2_ar_cell], LEFT, 0);
        break;
    }
    
}

void move_Y(int dirY = move_stop)
{   //true - RIGHT
    // false - LEFT
    switch(dirY)
    {
        case move_up:

            Dynamixel.turn(Conf.id_ar[Y_ar_cell], RIGHT, Conf.id_speed_ar[Y_ar_cell]);

        break;

        case move_stop:

             Dynamixel.turn(Conf.id_ar[Y_ar_cell], RIGHT, 0);

        break;

        case move_down:

             Dynamixel.turn(Conf.id_ar[Y_ar_cell], LEFT, Conf.id_speed_ar[Y_ar_cell]);

        break;
    }
}

void move_Z(int dirZ = move_stop, bool on1 = OFF, bool on2 = OFF, bool on3 = OFF, bool on4 = OFF)
{
    //true - RIGHT
    // false - LEFT
    switch(dirZ)
    {
        case move_up:

            if(on1 == ON)
                Dynamixel.turn(Conf.id_ar[Z1_ar_cell], RIGHT, Conf.id_speed_ar[Z1_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z1_ar_cell], RIGHT, 0);

            if(on2 == ON)
                Dynamixel.turn(Conf.id_ar[Z2_ar_cell], LEFT, Conf.id_speed_ar[Z2_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z2_ar_cell], LEFT, 0);

            if(on3 == ON)
                Dynamixel.turn(Conf.id_ar[Z3_ar_cell], RIGHT, Conf.id_speed_ar[Z3_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z3_ar_cell], RIGHT, 0);

            if(on4 == ON)
                Dynamixel.turn(Conf.id_ar[Z4_ar_cell], LEFT, Conf.id_speed_ar[Z4_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z4_ar_cell], LEFT, 0);

        break;

        case move_stop:

            Dynamixel.turn(Conf.id_ar[Z1_ar_cell], RIGHT, 0);
            Dynamixel.turn(Conf.id_ar[Z2_ar_cell], LEFT, 0);
            Dynamixel.turn(Conf.id_ar[Z3_ar_cell], RIGHT, 0);
            Dynamixel.turn(Conf.id_ar[Z4_ar_cell], LEFT, 0);

        break;

        case move_down:

            if(on1 == ON)
                Dynamixel.turn(Conf.id_ar[Z1_ar_cell], LEFT, Conf.id_speed_ar[Z1_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z1_ar_cell], LEFT, 0);

            if(on2 == ON)
                Dynamixel.turn(Conf.id_ar[Z2_ar_cell], RIGHT, Conf.id_speed_ar[Z2_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z2_ar_cell], RIGHT, 0);

            if(on3 == ON)
                Dynamixel.turn(Conf.id_ar[Z3_ar_cell], LEFT, Conf.id_speed_ar[Z3_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z3_ar_cell], LEFT, 0);

            if(on4 == ON)
                Dynamixel.turn(Conf.id_ar[Z4_ar_cell], RIGHT, Conf.id_speed_ar[Z4_ar_cell]);
            else
                Dynamixel.turn(Conf.id_ar[Z4_ar_cell], RIGHT, 0);

        break;
    }
}

void rotate_gripper(int deg)
{   
    deg =  constrain(deg, Conf.grip_rot[MAX_], Conf.grip_rot[MIN_]);
    Dynamixel.moveSpeed(Conf.Gripper_rotate_id, deg, Conf.id_speed_ar[Grip_rot_ar_cell]);
}

void gripper(int pol)
{
    pol =  constrain(pol, Conf.grip_pol[MAX_], Conf.grip_pol[MIN_]);
    Dynamixel.moveSpeed(Conf.Gripper_pol_id, pol, Conf.id_speed_ar[Grip_pol_ar_cell]);
}

void valve_st(bool st)
{
    switch (st){
        case MAX_:

            Dynamixel.moveSpeed(Conf.valve_id, Conf.valve_st[MAX_], Conf.id_speed_ar[valve_ar_cell]);
            break;

        case MIN_:

            Dynamixel.moveSpeed(Conf.valve_id, Conf.valve_st[MAX_], Conf.id_speed_ar[valve_ar_cell]);        
            break;
    }
}

///////////////////////////////////     ОТЛАДЧИКИ       ///////////////////////////////////////////////
void print_endstop_status(int chooseEnds = 3) // ФУНКЦИЯ ВЫВОДА СОСТОЯНИЙ КОНЦЕВИКОВ ( ЕСТЬ ВЫБОР ОСИ: ВСЕ;X;Y;Z)
{  
     switch(chooseEnds)
    {   
        case X_:
            COM.print("X1_end:");
            COM.print(X1.endstop_check());
            COM.print(" ");
            COM.print("X2_end:");
            COM.print(X2.endstop_check());
            COM.println(" ");
            break;
        
        case Y_:
            COM.print(Y.endstop_check());
            COM.println(" ");
            break;
        
        case Z_:
            COM.print("Z1_end:");
            COM.print(Z1.endstop_check());
            COM.print(" ");
            COM.print("Z2_end:");
            COM.print(Z2.endstop_check());
            COM.print(" ");
            COM.print("Z3_end:");
            COM.print(Z3.endstop_check());
            COM.print(" ");
            COM.print("Z4_end:");
            COM.println(Z4.endstop_check());
            break;

        case All:
            COM.print("X1_end:");
            COM.print(X1.endstop_check());
            COM.print(" ");
            COM.print("X2_end:");
            COM.print(X2.endstop_check());
            COM.print(" ");
            COM.print("Y_end:");
            COM.print(Y.endstop_check());
            COM.print(" ");
            COM.print("Z1_end:");
            COM.print(Z1.endstop_check());
            COM.print(" ");
            COM.print("Z2_end:");
            COM.print(Z2.endstop_check());
            COM.print(" ");
            COM.print("Z3_end:");
            COM.print(Z3.endstop_check());
            COM.print(" ");
            COM.print("Z4_end:");
            COM.println(Z4.endstop_check());
            break;
    }
    
}

void print_encoders_val(int chooseEnc = 3) // ФУНКЦИЯ ВЫВОДА КОЛИЧЕСТВА ТИКОВ ЭНКОДЕРОВ ( ЕСТЬ ВЫБОР ОСИ: ВСЕ;X;Y;Z)
{
    switch(chooseEnc)
    {
        case X_:
            COM.print("X1_enc:");
            COM.print(X1.getTiks());
            COM.print(" ");
            COM.print("X2_enc:");
            COM.print(X2.getTiks());
            COM.println(" ");
            break;

        case Y_:
            COM.print("Y_enc:");
            COM.print(Y.getTiks());
            COM.println(" ");
            break;
        
        case Z_:
            COM.print("Z1_enc");
            COM.print(Z1.getTiks());
            COM.print(" ");
            COM.print("Z2_enc");
            COM.print(Z2.getTiks());
            COM.print(" ");
            COM.print("Z3_enc");
            COM.print(Z3.getTiks());
            COM.print(" ");
            COM.print("Z4_enc");
            COM.print(Z4.getTiks());
            COM.println(" ");
            break;
        
        case All:
            COM.print("X1_enc:");
            COM.print(X1.getTiks());
            COM.print(" ");
            COM.print("X2_enc:");
            COM.print(X2.getTiks());
            COM.print(" ");
            COM.print("Y_enc:");
            COM.print(Y.getTiks());
            COM.print(" ");
            COM.print("Z1_enc:");
            COM.print(Z1.getTiks());
            COM.print(" ");
            COM.print("Z2_enc:");
            COM.print(Z2.getTiks());
            COM.print(" ");
            COM.print("Z3_enc:");
            COM.print(Z3.getTiks());
            COM.print(" ");
            COM.print("Z4_enc:");
            COM.println(Z4.getTiks());
            break;      
    }
}

void loop()
{
    
}
