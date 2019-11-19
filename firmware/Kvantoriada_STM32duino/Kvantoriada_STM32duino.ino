#include "libs/DynamixelSerial3/DynamixelSerial3.h"
// ВЫБОР ПОСЛЕДОВАТЕЛЬНО ПОРТА ДЛЯ ОТЛАДКИ 
#define COM Serial
//#define COM Serial2

// ПАРАМЕТРЫ РАБОЧЕГО ПРОСТРАНСТВА
#define WS_X_size 740
#define WS_Y_size 740
#define WS_Z_size 740

#define CELL_X_size 10
#define CELL_Y_size 10
#define CELL_Z_size 10

#define Wheel_deametr 55
#define Wheel_ticks 65

const int cell_Size[3] = {CELL_X_size, CELL_Y_size, CELL_Z_size};
const int ws_Size[3] = {WS_X_size, WS_Y_size, WS_Z_size};

// ПЕРЕМЕННЫЕ ДЛЯ ВЫБОРА ОСЕЙ В ФУНКЦИЯХ 
#define X_ 0
#define Y_ 1
#define Z_ 2

#define Z1
#define Z2
#define Z3
#define Z4

#define X1
#define X2

#define Y

// ПЕРЕМЕННЫЕ ДЛЯ ВЫБОРА ЯЧЕЕК В МАССИВАХ
#define Z1_arcell 0 // ЯЧЕЙКА ОСИ Z1
#define Z2_arcell 1 // ЯЧЕЙКА ОСИ Z2
#define Z3_arcell 2 // ЯЧЕЙКА ОСИ Z3
#define Z4_arcell 3 // ЯЧЕЙКА ОСИ Z4

#define X1_arcell 4 // ЯЧЕЙКА ОСИ X1
#define X2_arcell 5 // ЯЧЕЙКА ОСИ X2

#define Y_arcell 6 // ЯЧЕЙКА ОСИ Y

// ID СЕРВОМОТОРОВ
#define Dynamixel_count 10 //КОЛИЧЕСТВО СЕРВОМОТОРОВ В СИСТЕМЕ
#define Z1_dyn_id 1 // ID ДИНАМИКСЕЛЯ ОСИ Z1
#define Z2_dyn_id 2 // ID ДИНАМИКСЕЛЯ ОСИ Z2
#define Z3_dyn_id 3 // ID ДИНАМИКСЕЛЯ ОСИ Z3
#define Z4_dyn_id 4 // ID ДИНАМИКСЕЛЯ ОСИ Z4

#define X1_dyn_id 5 // ID ДИНАМИКСЕЛЯ ОСИ X1
#define X2_dyn_id 6 // ID ДИНАМИКСЕЛЯ ОСИ X2

#define Y_dyn_id 7 // ID ДИНАМИКСЕЛЯ ОСИ Y

#define valve_dyn_id 8 // ID ДИНАМИКСЕЛЯ КЛАПАНА
#define rot_grip_dyn_id 9 // ID ДИНАМИКСЕЛЯ ПОВОРОТА КЛЕШНИ
#define grip_pos_dyn_id 10 // ID ДИНАМИКСЕЛЯ ОТКРЫТИЯ/ЗАКРЫТИЯ ЗАХВАТА

#define com_dir_pin 23 // ПИН УПРАВЛЕНИЯ МИКРОСХЕМОЙ

const int dyn_id_ar[Dynamixel_count] = { // МАССИВ ID СЕРВОМОТОРОВ
                            Z1_dyn_id, 
                            Z2_dyn_id,
                            Z3_dyn_id, 
                            Z4_dyn_id,
                            X1_dyn_id, 
                            X2_dyn_id,
                            Y_dyn_id,
                            valve_dyn_id,
                            rot_grip_dyn_id, 
                            grip_pos_dyn_id 
                          };
                         
// ПИНЫ ЭНКОДЕРОВ ОСЕЙ  
#define encoder_count 7 // КОЛИЧЕСТВО ЭНКОДЕРОВ В СИСТЕМЕ

#define Z1_encoder_pin  PC15 // ПИН ЭНКОДЕРА ОСИ Z1
#define Z2_encoder_pin  PA1  // ПИН ЭНКОДЕРА ОСИ Z2
#define Z3_encoder_pin  PC14 // ПИН ЭНКОДЕРА ОСИ Z3
#define Z4_encoder_pin  PB13 // ПИН ЭНКОДЕРА ОСИ Z4

#define X16_encoder_pin PA3 // ПИН ЭНКОДЕРА ОСИ X1
#define X15_encoder_pin PA2 // ПИН ЭНКОДЕРА ОСИ X2

#define Y_encoder_pin   PA0 // ПИН ЭНКОДЕРА ОСИ Y


const int encoder_pins_array[7] = {  // МАССИВ ПИНОВ ЭНКОДЕРОВ ОСЕЙ 
                                        Z1_encoder_pin, 
                                        Z2_encoder_pin, 
                                        Z3_encoder_pin,
                                        Z4_encoder_pin,
                                        X15_encoder_pin, 
                                        X16_encoder_pin, 
                                        Y_encoder_pin
                                  };
int encoder_value[7] = {0, 0, 0, 0, 0, 0, 0}; // МААСИВ ЗНАЧЕНИЙ ЭНКОДЕРОВ

// ПИНЫ КОНЦЕВИКОВ ОСЕЙ
#define endstop_count 7 // КОЛИЧЕСТВО КОНЦЕВИКОВ В СИСТЕМЕ

#define Z1_endstop_pin  PA6 // ПИН КОНЦЕВИКА ОСИ Z1
#define Z2_endstop_pin  PA4 // ПИН КОНЦЕВИКА ОСИ Z2
#define Z3_endstop_pin  PB0 // ПИН КОНЦЕВИКА ОСИ Z3
#define Z4_endstop_pin  PB1 // ПИН КОНЦЕВИКА ОСИ Z4

#define X15_endstop_pin PA5 // ПИН КОНЦЕВИКА ОСИ X1
#define X16_endstop_pin PA7 // ПИН КОНЦЕВИКА ОСИ X2

#define Y_endstop_pin PB14 // ПИН КОНЦЕВИКА ОСИ Y

bool endstop_read[endstop_count] = {false, false, false, false, false, false, false}; // МАССИВ СОСТОЯНИЙ КОНЦЕВИКОВ
const int endstops_pins_array[endstop_count] =  { //МАССИВ ПИНОВ КОНЦЕВИКОВ
                                                    Z1_endstop_pin, 
                                                    Z2_endstop_pin, 
                                                    Z3_endstop_pin,
                                                    Z4_endstop_pin,
                                                    X15_endstop_pin,
                                                    X16_endstop_pin, 
                                                    Y_endstop_pin
                                                };



void setup()
{
  com_init(); // ИНИЦИАЛИЗЯЦИЯ ПОСЛЕДОВАТЕЛЬНОГО ПОРТА
  pins_init();// ИНИЦИАЛИЗЯЦИЯ ПИНОВ 
  encoders_init(); // ИНИЦИАЛИЗАЦИЯ ЭНКОДЕРОВ
}

void pins_init()
{
  for (int i = 0; i < endstop_count; i++)
  {
    pinMode(endstops_pins_array[i], INPUT);
    delay(5);
  }
  for (int i = 0; i < encoder_count; i++)
  {
    pinMode(encoder_pins_array[i], INPUT);
    delay(5);
  }
}

void com_init()
{
  COM.begin(115200);
  COM.println("Ready");
}

void encoders_init()
{
  attachInterrupt(encoder_pins_array[Z1_arcell], Z1_counter, RISING);
  attachInterrupt(encoder_pins_array[Z2_arcell], Z2_counter, RISING);
  attachInterrupt(encoder_pins_array[Z3_arcell], Z3_counter, RISING);
  attachInterrupt(encoder_pins_array[Z4_arcell], Z4_counter, RISING);

  attachInterrupt(encoder_pins_array[X1_arcell], X1_counter, RISING);
  attachInterrupt(encoder_pins_array[X2_arcell], X2_counter, RISING);

  attachInterrupt(encoder_pins_array[Y_arcell], Y_counter, RISING);
}
void read_endstops()
{
  for(int i = 0; i < endstop_count; i++)
  {
    endstop_read[i] = digitalRead(endstops_pins_array[i]);
  }
}
void print_endstops()
{
  for(int i = 0; i < endstop_count; i++)
  {
    read_endstops();
    COM.print(endstop_read[i] + ' ');
  }
  COM.println();
}

void print_encoders()
{
  for (int i = 0; i < encoder_count; i++)
  {
    COM.print(encoder_value[i] + ' ');
  }
}
void Dynamixel_init()
{
  Dynamixel.begin(1000000,com_dir_pin);
  for (int i = 0; i < Dynamixel_count; i++)
  {
    if (Dynamixel.ping(dyn_id_ar[i]))
    {
      
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////
void loop()
{


}
/////////////////////////////////////////////////////////////////////////////////////
void Z1_counter()
{
  encoder_value[Z1_arcell]++;
}

void Z2_counter()
{
  encoder_value[Z2_arcell]++;
}

void Z3_counter()
{
  encoder_value[Z3_arcell]++;
}

void Z4_counter()
{
  encoder_value[Z4_arcell]++;
}

void X1_counter()
{
  encoder_value[X1_arcell]++;
}

void X2_counter()
{
  encoder_value[X2_arcell]++;
}

void Y_counter()
{
  encoder_value[Y_arcell]++;
}