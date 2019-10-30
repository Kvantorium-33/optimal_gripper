#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" 
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif  

#define COM Serial2                                                 // BLUETOOTH
//#define COM SerialUSB                                             // USB
////////////////// ПОДКЛЮЧЕНИЕ РАБОЧИХ БИБЛИОТЕК ///////////////////////
#include "Libs/Robot_libs/Axis/Axis.h"                              // БИБЛИОТЕКА ОСЕЙ 
#include "Libs/Robot_libs/Workspace/Workspace.h"                    // БИБЛИОТЕКА РАБОЧЕГО ПРОСТРАНСТВА
#include "Libs/ROS_DYN/DynamixelWorkbench/src/DynamixelWorkbench.h" // БИБЛИОТЕКА СЕРВОМОТОРОВ DynamixelWorkbench  
#include "Libs/Robot_libs/Mathematics/Mathematics.h"                // БИБЛИОТЕКА МАТЕМАТИКИ  
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
DynamixelWorkbench Dxl;                                             // ОБЪЕКТ ШИНЫ DXL ДЛЯ УПРАВЛЕНИЯ СЕРВОМОТОРАМИ
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
    X1.endstop_mode(ENDMODE_INTERR);                                // ПЕРЕВОД КОНЦЕВИКА ОСИ Х1 НА ОБРАБОТЧИК ПРЕРЫВАНИЯ 
    //////////////////////////    X2    ////////////////////////////////
    X2.Ainit(Conf.X2_id, PC.X2_endstop_pin, PC.X2_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Х2
    X2.endstop_mode(ENDMODE_INTERR);                                // ПЕРЕВОД КОНЦЕВИКА ОСИ Х2 НА ОБРАБОТЧИК ПРЕРЫВАНИЯ                            
    //////////////////////////    Y    /////////////////////////////////
    Y.Ainit(Conf.Y_id, PC.Y_endstop_pin, PC.Y_encoder_pin);         // ИНИЦИАЛИЗАЦИ ОСИ Y
    Y.endstop_mode(ENDMODE_INTERR);                                 // ПЕРЕВОД КОНЦЕВИКА ОСИ Y НА ОБРАБОТЧИК ПРЕРЫВАНИЯ 
    //////////////////////////    Z1    ////////////////////////////////
    Z1.Ainit(Conf.Z1_id, PC.Z1_endstop_pin, PC.Z1_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z1 
    Z1.endstop_mode(ENDMODE_INTERR);                                // ПЕРЕВОД КОНЦЕВИКА ОСИ Z1 НА ОБРАБОТЧИК ПРЕРЫВАНИЯ 
    //////////////////////////    Z2    ////////////////////////////////
    Z2.Ainit(Conf.Z2_id, PC.Z2_endstop_pin, PC.Z2_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z2
    Z2.endstop_mode(ENDMODE_INTERR);                                // ПЕРЕВОД КОНЦЕВИКА ОСИ Z2 НА ОБРАБОТЧИК ПРЕРЫВАНИЯ 
    //////////////////////////    Z3    ////////////////////////////////
    Z3.Ainit(Conf.Z3_id, PC.Z3_endstop_pin, PC.Z3_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z3
    Z3.endstop_mode(ENDMODE_INTERR);                                // ПЕРЕВОД КОНЦЕВИКА ОСИ Z3 НА ОБРАБОТЧИК ПРЕРЫВАНИЯ                           
    //////////////////////////    Z4    ////////////////////////////////
    Z4.Ainit(Conf.Z4_id, PC.Z4_endstop_pin, PC.Z4_encoder_pin);     // ИНИЦИАЛИЗАЦИЯ ОСИ Z4 
    Z4.endstop_mode(ENDMODE_INTERR);                                // ПЕРЕВОД КОНЦЕВИКА ОСИ Z4 НА ОБРАБОТЧИК ПРЕРЫВАНИЯ                               
    ///////////////////////// ПОДГОТОВКА РАБОЧЕГО ПРОСТРАНСТВА /////////
    WS.set_ws_size(ws_Size[X_], ws_Size[Y_], ws_Size[Z_]);          // УСТАНОВКА  РАЗМЕРОВ РАБОЧЕГО ПРОСТРАНСТВА (формат XYZ) 
    WS.set_cell_size(cell_Size[X_], cell_Size[Y_], cell_Size[Z_]);  // УСТАНОВКА РАЗМЕРОВ ЯЧЕЙКА (формат XYZ)
    ////////////////////////////////////////////////////////////////////
    Math.setWheelDeametr(Wheel_deametr);                            // УСТАНОВКА ДИАМЕТРА КОЛЕСА ЭНКОДЕРА
    Math.setWheelTiks(Wheel_ticks);                                 // УСТАНОВКА КОЛИЧЕСТВА ТИКОВ НА ОБОРОТ КОЛЕСА ЭНКОДЕРА
    Math.putWSs(ws_Size[X_], ws_Size[Y_], ws_Size[Z_]);             // УСТАНОВКА  РАЗМЕРОВ РАБОЧЕГО ПРОСТРАНСТВА ДЛЯ МАТЕМАТИКИ (формат XYZ) 
    Math.puCells(cell_Size[X_], cell_Size[Y_], cell_Size[Z_]);      // УСТАНОВКА РАЗМЕРОВ ЯЧЕЙКА ДЛЯ МАТЕМАТИКИ (формат XYZ)
    ///////////////////////// ПОДГОТОВКА МОТОРОВ ///////////////////////
    DXL_init();                                                     // ИНИЦИАЛИЗАЦИЯ ШИНЫ DXL
    servomotors_init();                                             // ИНИЦИАЛИЗАЦИЯ СЕРВОМОТОРОВ

}

void loop()
{
    
}

void DXL_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ ШИНЫ DXL
{   
    bool init_res = false;

    while (!init_res)
    {
        init_res = Dxl.init(DEVICE_NAME, Conf.DXL_BAUDRATE, &Conf.log);
    }
    ///// ТЕКСТОВОЕ СОПРОВОЖДЕНИЕ
}

void servomotors_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ СЕРВОМОТОРОВ
{   int count = 0;
    for (uint8_t i = 0; i < Conf.motor_count; i++)
    {
        bool ping_check = false;
        while(!ping_check || count != 300)
        {
            ///// ТЕКСТОВОЕ СОПРОВОЖДЕНИЕ
            Dxl.ping(Conf.id_ar[i], &Conf.model_number, &Conf.log);

             count++;
        }   
        ///// ТЕКСТОВОЕ СОПРОВОЖДЕНИЕ 
        count = 0; 
        bool change_mode = false;
        while(!change_mode || count != 300)
        {
            Dxl.wheelMode(Conf.id_ar[i], Conf.id_accel_ar[i], &Conf.log);
         ///// ТЕКСТОВОЕ СОПРОВОЖДЕНИЕ 
        }
         ///// ТЕКСТОВОЕ СОПРОВОЖДЕНИЕ 
    }
}

void move_X(int dirX, bool on1 = true, bool on2 = true) // ФУНКЦИЯ ПЕРЕМЕЩЕНИЯ ОСИ Х
{
    switch (dirX)
    {
    case move_up:
        if (on1 == true)
            Dxl.goalVelocity(Conf.X1_id, Conf.id_speed_ar[X1_ar_cell]);
        else 
            Dxl.goalVelocity(Conf.X1_id, (int32_t)0);

        if (on2 == true)
            Dxl.goalVelocity(Conf.X2_id, -Conf.id_speed_ar[X2_ar_cell]);
        else
            Dxl.goalVelocity(Conf.X2_id, (int32_t)0);

        break;

    case move_stop:
        Dxl.goalVelocity(Conf.X1_id, (int32_t)0);
        Dxl.goalVelocity(Conf.X2_id, (int32_t)0);
        break;

    case move_down:
        if (on1 == true)
            Dxl.goalVelocity(Conf.X1_id, -Conf.id_speed_ar[X1_ar_cell]);
        else 
            Dxl.goalVelocity(Conf.X1_id, (int32_t)0);

        if (on2 == true)
            Dxl.goalVelocity(Conf.X2_id, Conf.id_speed_ar[X2_ar_cell]);
        else
            Dxl.goalVelocity(Conf.X2_id, (int32_t)0);
    }
}

void move_Y(int dirY = 0) // ФУНКЦИЯ ПЕРЕМЕЩЕНИЯ ОСИ Y
{
    switch(dirY)
    {
        case move_up:
            Dxl.goalVelocity(Conf.Y_id, Conf.id_speed_ar[Y_ar_cell]);
            break;

        case move_stop:
            Dxl.goalVelocity(Conf.Y_id,(int32_t)0);
            break;

        case move_down:
            Dxl.goalVelocity(Conf.Y_id, -Conf.id_speed_ar[Y_ar_cell]);
    }
}

void move_Z(int dirZ, bool on1 = true, bool on2 = true, bool on3 = true, bool on4 = true) // ФУНКЦИЯ ПЕРЕМЕЩЕНИЯ ОСИ Y
{
    switch(dirZ)
    {
        case move_up:

            if (on1 == true)
                Dxl.goalVelocity(Conf.Z1_id, Conf.id_speed_ar[Z1_ar_cell]);
            else 
                Dxl.goalVelocity(Conf.Z1_id, (int32_t)0);
 
            if (on2 == true)
                Dxl.goalVelocity(Conf.Z2_id, -Conf.id_speed_ar[Z2_ar_cell]);
            else
                Dxl.goalVelocity(Conf.Z2_id, (int32_t)0);
            
            if (on3 == true)
                Dxl.goalVelocity(Conf.Z3_id, -Conf.id_speed_ar[Z3_ar_cell]);
            else 
                Dxl.goalVelocity(Conf.Z3_id, (int32_t)0);

            if (on4 == true)
                Dxl.goalVelocity(Conf.Z4_id, Conf.id_speed_ar[Z4_ar_cell]);
            else 
                Dxl.goalVelocity(Conf.Z4_id, (int32_t)0);

            break;

        case move_stop:
            Dxl.goalVelocity(Conf.Z1_id, (int32_t)0);
            Dxl.goalVelocity(Conf.Z2_id, (int32_t)0);
            Dxl.goalVelocity(Conf.Z3_id, (int32_t)0);
            Dxl.goalVelocity(Conf.Z4_id, (int32_t)0);
            break;
        
        case move_down:
            if (on1 == true)
                Dxl.goalVelocity(Conf.Z1_id, -Conf.id_speed_ar[Z1_ar_cell]);
            else 
                 Dxl.goalVelocity(Conf.Z1_id, (int32_t)0);

            if (on2 == true)
                Dxl.goalVelocity(Conf.Z2_id, Conf.id_speed_ar[Z2_ar_cell]);
            else 
                Dxl.goalVelocity(Conf.Z2_id, (int32_t)0);

            if (on3 == true)
                Dxl.goalVelocity(Conf.Z3_id, Conf.id_speed_ar[Z3_ar_cell]);
            else 
                Dxl.goalVelocity(Conf.Z3_id, (int32_t)0);

            if (on4 == true)
                Dxl.goalVelocity(Conf.Z4_id, -Conf.id_speed_ar[Z4_ar_cell]);
            else 
                Dxl.goalVelocity(Conf.Z4_id, (int32_t)0);
            break;
    }
}
void move_home() // ФУНКЦИЯ ВОЗВРАТА ДОМОЙ
{
    while (Z1.endstop_check() != true && Z2.endstop_check() != true  && Z3.endstop_check() != true && Z4.endstop_check() != true)
    {                           
        move_Z(move_up, ON, ON, ON, ON);
    }
    move_Z(move_stop, OFF, OFF, OFF,OFF);
    
    while (X1.endstop_check() != true && X2.endstop_check() != true)
    {
        move_X(move_down, ON, ON);
    }
    move_X(move_stop, OFF, OFF);

    while  (Y.endstop_check() != true)
    {
        move_Y(move_down);
    }
    move_Y(move_stop);

    //   СБРОС ЗНАЧЕНИЙ ЭНКОДЕРОВ ОСЕЙ
    Z1.reload();
    Z2.reload();
    Z3.reload();
    Z4.reload();

    X1.reload();
    X2.reload();

    Y.reload();
}

void gotuda(int Xcor, int Ycor, int Zcor) // ФУНКЦИЯ ПЕРЕМЕЩЕНИЯ  ПО КООРДИНАТАМ
{   
      /// расчет тиков 
        int needTiks[3] =   {   Math.getTicks(X_, Xcor, lastPos[X_]),  
                                Math.getTicks(Y_, Ycor, lastPos[Y_]),
                                Math.getTicks(Z_, Zcor, lastPos[Z_])
                            };
      ///  обработчик направлений для моторов на основе числа тиков относительно нуля
        int reverse[3]  =   {false, false, false};
        if (needTiks[X_] < 0)
            reverse[X_] = true;

        if (needTiks[Y_] < 0)
            reverse[Y_] = true;

        if (needTiks[Z_] < 0)
            reverse[Z_] = true;

        Z1.reload();
        Z2.reload();
        Z3.reload();
        Z4.reload();

        X1.reload();
        X2.reload();

        Y.reload();
      ///   движение осей на кол-во тиков 
        do
        {
            
        } while   (X1.encoder_counter() != needTiks[X_] && X2.encoder_counter() != needTiks[X_] && Y.encoder_counter() != needTiks[Y_] && 
        Z1.encoder_counter() != needTiks[Z_] && Z2.encoder_counter() != needTiks[Z_] && Z3.encoder_counter() != needTiks[Z_] && Z4.encoder_counter() != needTiks[Z_]);
}

void com_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ ПОСЛЕДОВАТЕЛЬНО ПОРТА
{   
    

 
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
            COM.print(X1.encoder_counter());
            COM.print(" ");
            COM.print("X2_enc:");
            COM.print(X2.encoder_counter());
            COM.println(" ");
            break;

        case Y_:
            COM.print("Y_enc:");
            COM.print(Y.encoder_counter());
            COM.println(" ");
            break;
        
        case Z_:
            COM.print("Z1_enc");
            COM.print(Z1.encoder_counter());
            COM.print(" ");
            COM.print("Z2_enc");
            COM.print(Z2.encoder_counter());
            COM.print(" ");
            COM.print("Z3_enc");
            COM.print(Z3.encoder_counter());
            COM.print(" ");
            COM.print("Z4_enc");
            COM.print(Z4.encoder_counter());
            COM.println(" ");
            break;
        
        case All:
            COM.print("X1_enc:");
            COM.print(X1.encoder_counter());
            COM.print(" ");
            COM.print("X2_enc:");
            COM.print(X2.encoder_counter());
            COM.print(" ");
            COM.print("Y_enc:");
            COM.print(Y.encoder_counter());
            COM.print(" ");
            COM.print("Z1_enc:");
            COM.print(Z1.encoder_counter());
            COM.print(" ");
            COM.print("Z2_enc:");
            COM.print(Z2.encoder_counter());
            COM.print(" ");
            COM.print("Z3_enc:");
            COM.print(Z3.encoder_counter());
            COM.print(" ");
            COM.print("Z4_enc:");
            COM.println(Z4.encoder_counter());
            break;      
    }
}
