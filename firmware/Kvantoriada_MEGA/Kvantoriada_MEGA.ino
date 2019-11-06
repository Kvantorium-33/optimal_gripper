
//#define COM Serial2                                                // BLUETOOTH
#define COM Serial                                                   // USB
////////////////// ПОДКЛЮЧЕНИЕ РАБОЧИХ БИБЛИОТЕК ///////////////////////
#include <Axis.h>                                                   // БИБЛИОТЕКА ОСЕЙ 
#include <Workspace.h>                                              // БИБЛИОТЕКА РАБОЧЕГО ПРОСТРАНСТВА
#include <Mathematics.h>                                            // БИБЛИОТЕКА МАТЕМАТИКИ  
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

}


void com_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ ПОСЛЕДОВАТЕЛЬНО ПОРТА
{   
    COM.begin(Conf.COM_BAUDRATE);
    COM.println("Hello"); 
};

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
