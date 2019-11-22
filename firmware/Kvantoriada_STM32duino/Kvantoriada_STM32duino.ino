#include <ros.h> //  БИБЛИОТЕКА ПОДКЛЮЧЕНИЯ К ВЫСШЕЙ СИЛЕ
#include <DynamixelSerial3.h> // БИБЛИОТЕКА ДЛЯ УПРАВЛЕНИЯ ДИНАМИКСЕЛЯМИ
#define DXL_baud 1000000
// ВЫБОР ПОСЛЕДОВАТЕЛЬНО ПОРТА ДЛЯ ОТЛАДКИ
#define COM Serial
//#define COM Serial1
#define COM_baud 115200

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

int nextPos[3] = {0, 0, 0};
int lastPos[3] = {0, 0, 0};
// ПЕРЕМЕННЫЕ ДЛЯ ВЫБОРА ОСЕЙ В ФУНКЦИЯХ И ТРОЙНЫХ МАССИВАХ 
#define _X_ 0
#define _Y_ 1
#define _Z_ 2

//#define Z1
//#define Z2
//#define Z3
//#define Z4
//
//#define X1
//#define X2
//
//#define Y

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

#define com_dir_pin PB1 // ПИН УПРАВЛЕНИЯ МИКРОСХЕМОЙ

int dyn_id_ar[Dynamixel_count] = // МАССИВ ID СЕРВОМОТОРОВ
{ 
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

#define Z1_encoder_pin  PA0 // ПИН ЭНКОДЕРА ОСИ Z1
#define Z2_encoder_pin  PA1  // ПИН ЭНКОДЕРА ОСИ Z2
#define Z3_encoder_pin  PA2 // ПИН ЭНКОДЕРА ОСИ Z3
#define Z4_encoder_pin  PA3 // ПИН ЭНКОДЕРА ОСИ Z4

#define X16_encoder_pin PB5 // ПИН ЭНКОДЕРА ОСИ X1
#define X15_encoder_pin PB4 // ПИН ЭНКОДЕРА ОСИ X2

#define Y_encoder_pin   PB15 // ПИН ЭНКОДЕРА ОСИ Y


const int encoder_pins_array[7] = // МАССИВ ПИНОВ ЭНКОДЕРОВ ОСЕЙ
{  
  Z1_encoder_pin,
  Z2_encoder_pin,
  Z3_encoder_pin,
  Z4_encoder_pin,
  X15_encoder_pin,
  X16_encoder_pin,
  Y_encoder_pin
};
int Z1_enc_value = 0;
int Z2_enc_value = 0;
int Z3_enc_value = 0;
int Z4_enc_value = 0;

int X1_enc_value = 0;
int X2_enc_value = 0;

int Y_enc_value = 0;

// ПИНЫ КОНЦЕВИКОВ ОСЕЙ
#define endstop_count 7 // КОЛИЧЕСТВО КОНЦЕВИКОВ В СИСТЕМЕ

#define Z1_endstop_pin  PA6 // ПИН КОНЦЕВИКА ОСИ Z1
#define Z2_endstop_pin  PA4 // ПИН КОНЦЕВИКА ОСИ Z2
#define Z3_endstop_pin  PB0 // ПИН КОНЦЕВИКА ОСИ Z3
#define Z4_endstop_pin  PB12 // ПИН КОНЦЕВИКА ОСИ Z4

#define X15_endstop_pin PA5 // ПИН КОНЦЕВИКА ОСИ X1
#define X16_endstop_pin PA7 // ПИН КОНЦЕВИКА ОСИ X2

#define Y_endstop_pin PB13 // ПИН КОНЦЕВИКА ОСИ Y

bool endstop_read[endstop_count] = {false, false, false, false, false, false, false}; // МАССИВ СОСТОЯНИЙ КОНЦЕВИКОВ

const int endstops_pins_array[endstop_count] =  //МАССИВ ПИНОВ КОНЦЕВИКОВ
{ 
  Z1_endstop_pin,
  Z2_endstop_pin,
  Z3_endstop_pin,
  Z4_endstop_pin,
  X15_endstop_pin,
  X16_endstop_pin,
  Y_endstop_pin
};

#define KpX 0 // ПРОПОРЦИОНАЛЬНЫЙ КОЭФФИЦЕНТ РЕГУЛЯТОРА ОСИ Х
#define KpZ12 0 // ПРОПОРЦИОНАЛЬНЫЙ КОЭФФИЦЕНТ РЕГУЛЯТОРА ОСИ Z1 И Z2
#define KpZ34 0 // ПРОПОРЦИОНАЛЬНЫЙ КОЭФФИЦЕНТ РЕГУЛЯТОРА ОСИ Z3 И Z4
#define KpZ 0 // ПРОПОРЦИОНАЛЬНЫЙ КОЭФФИЦЕНТ РЕГУЛЯТОРА ОСИ 

#define move_up 1     // ДВИЖЕНИЕ ОСИ ПО УВЕЛЕЧЕНИЮ КООРДИНАТ
#define move_stop 0   // НЕДВИЖЕНИЕ ОСИ
#define move_down -1  // ДВИЖЕНИЕ ОСИ ПО УМЕНЬШЕНИЮ КООРДИНАТ

int Z1_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ КАРЕТКИ Z1
int Z2_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ КАРЕТКИ Z2
int Z3_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ КАРЕТКИ Z3
int Z4_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ КАРЕТКИ Z4

int X1_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ КАРЕТКИ X1
int X2_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ КАРЕТКИ X2

int Y_speed = 1020;  // СКОРОСТЬ ДИНАМИКСЕЛЯ КАРЕТКИ Y

int valve_speed = 1020;  // СКОРОСТЬ ДИНАМИКСЕЛЯ КЛАПАНА
int rot_grip_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ ПОВОРОТА ЗАХВАТА
int grip_pos_speed = 1020; // СКОРОСТЬ ДИНАМИКСЕЛЯ ЗАХВАТА

int speed_ar[Dynamixel_count] = {Z1_speed, Z2_speed, Z3_speed, Z4_speed, X1_speed, X2_speed, Y_speed, valve_speed, rot_grip_speed, grip_pos_speed};

#define LEFT false
#define RIGHT true
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup()
{
  com_init(); // ИНИЦИАЛИЗЯЦИЯ ПОСЛЕДОВАТЕЛЬНОГО ПОРТА
  pins_init();// ИНИЦИАЛИЗЯЦИЯ ПИНОВ
  encoders_init(); // ИНИЦИАЛИЗАЦИЯ ЭНКОДЕРОВ
  Dynamixel_init(); // ИНИЦИАЛИЗЯЦИЯ СИСТЕМЫ ДЛЯ ДИНАМИКСЕЛЕЙ
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pins_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ ПИНОВ
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

void com_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ ПОСЛЕДОВАТЕЛЬНОГО ПОРТА
{
  COM.begin(COM_baud);
  while (!COM);
  COM.println("Ready");
}

void encoders_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ ПРЕРЫВАНИЙ ЭНКОДЕРОВ
{
  attachInterrupt(digitalPinToInterrupt(encoder_pins_array[Z1_arcell]), Z1_counter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_pins_array[Z2_arcell]), Z2_counter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_pins_array[Z3_arcell]), Z3_counter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_pins_array[Z4_arcell]), Z4_counter, CHANGE);

  attachInterrupt(digitalPinToInterrupt(encoder_pins_array[X1_arcell]), X1_counter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_pins_array[X2_arcell]), X2_counter, CHANGE);

  attachInterrupt(digitalPinToInterrupt(encoder_pins_array[Y_arcell]), Y_counter, CHANGE);
}
void read_endstops() // ФУНКЦИЯ СЧИТЫВАНИЯ СОСТОЯНИЙ КОНЦЕВИКОВ
{
  for (int i = 0; i < endstop_count; i++)
  {
    endstop_read[i] = digitalRead(endstops_pins_array[i]);
  }
}
void print_endstops() // ФУНКЦИЯ ВЫВОДА СОСТОЯНИЙ КОНЦЕВИКОВ
{
   for (int i = 0; i < endstop_count; i++)
  {
    read_endstops();
    COM.print(endstop_read[i]);
    COM.print(" ");
  }
  COM.println();
}

void print_encoders() // ФУНКЦИЯ ВЫВОДА СЧЕТЧИКОВ ЭНКОДЕРОВ
{
  COM.print(Z1_enc_value);
  COM.print(" ");
  COM.print(Z2_enc_value);
  COM.print(" ");
  COM.print(Z3_enc_value);
  COM.print(" ");
  COM.print(Z4_enc_value);
  COM.print(" ");
  COM.print(X1_enc_value);
  COM.print(" ");
  COM.print(X2_enc_value);
  COM.print(" ");
  COM.print(Y_enc_value);
  COM.println();
}

void Dynamixel_init() // ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ СЕРВОМОТОРОВ
{
  Dynamixel.begin(DXL_baud, com_dir_pin, com_dir_pin); // начинаем связь с динамикселями на скорости 1 Mbps
  for (int i = 0; i < Dynamixel_count; i++) // пробегаемся по массиву айдишников динамикселей
  { 
    if (Dynamixel.ping(dyn_id_ar[i]) == 1) // стучимся к динамикселю с id из массива
    { // если достучались то пишем об успехе
      COM.print("Successfully connect to id: ");
      COM.println(i + 1);
    }
    else
    { // иначе пишем об ошибке
      COM.print("FAILED connect to id: ");
      COM.println(i + 1);
      while(1) //полностью тормозим программу 
      {
        COM.println(" NOT ALL DYNAMIXELS ARE CONNECTED AND INITED!!!!!! PLEASE CHECK ALL!!!");
      }
    }
    delay(500);
  }
}

void move_X(int mode = 0, bool on1 = false, bool on2 = false) // ФУНКЦИЯ ПЕРЕМЕЩЕНИЯ ОСИ X
{
  int dX = X1_enc_value - X2_enc_value; // НАХОДИМ РАЗНОСТЬ ЭНКОДЕРОВ КАРЕТОК Х1 И Х2
  int dx_speed =  dX * KpX; // УМНОЖАЕМ НА ПРОПОРЦИОНАЛЬНЫЙ КОЭФФИЦЕНТ ОСИ Х
  int X1_sp = abs(speed_ar[X1_arcell] - dx_speed); // ВЫЧИТАЕМ ИЗ УСТАНВЛОЕННОЙ СКОРОСТИ ДЛЯ КАРЕТКИ Х1 И ДЕЛАЕМ АБСОЛЮТНЫМ (ПО МОДУЛЮ)
  int X2_sp = abs(speed_ar[X2_arcell] + dx_speed); // ВЫЧИТАЕМ ИЗ УСТАНВЛОЕННОЙ СКОРОСТИ ДЛЯ КАРЕТКИ Х2 И ДЕЛАЕМ АБСОЛЮТНЫМ (ПО МОДУЛЮ)
  X1_sp = constrain(X1_sp, 0, 1020);  // ОГРАНИЧИВАЕМ НУЖНУЮ СКОРСТЬ В ПРЕДЕЛАХ МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ ДЛЯ КАРЕТКИ Х1
  X2_sp = constrain(X2_sp, 0, 1020);  // ОГРАНИЧИВАЕМ НУЖНУЮ СКОРСТЬ В ПРЕДЕЛАХ МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ ДЛЯ КАРЕТКИ Х2

    switch (mode) // СМОТРИМ КАКОЙ РЕЖИМ У НАС ПРОСЯТ
    { 
      case move_up: // ЕДЕМ ВПЕРЕД (В СТОРОНУ УВЕЛЕЧЕНИЯ КООРДИНАТЫ)
        if (on1 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X1_arcell], LEFT, X1_sp);
        else // ИНАЧЕ НЕ  ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X1_arcell], LEFT, 0);

        if (on2 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X2_arcell], RIGHT, X2_sp);
        else // ИНАЧЕ НЕ ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X2_arcell], RIGHT, 0);
      break;
      case move_stop: //ПОЛНЫЙ СТОП!!!!
        Dynamixel.turn(dyn_id_ar[X1_arcell], LEFT, 0);
        Dynamixel.turn(dyn_id_ar[X2_arcell], RIGHT, 0);
      break;
      case move_down: // ЕДЕМ НАЗАД (В СТОРОНУ УМЕНЬШЕНИЯ КООРДИНАТЫ)
        if (on1 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X1_arcell], RIGTH, X1_sp);
        else// ИНАЧЕ НЕ  ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X1_arcell], LEFT, 0);

        if (on2 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X2_arcell], LEFT, X2_sp);
        else // ИНАЧЕ НЕ ДВИГАЕМСЯ
          Dynamixel.turn(dyn_id_ar[X2_arcell], RIGHT, 0);
      break;
    }
}

void move_Z(int mode = 0, bool on1 = false, bool on2 = false, int on3 = false, int on4 = false) // ФУНКЦИЯ ПЕРЕМЕЩЕНИЯ ОСИ Z
{ 
  int dZ12 = Z1_enc_value - Z2_enc_value; // НАХОДИМ РАЗНОСТЬ 1-ОЙ И 2-ОЙ КАРЕТОК
  int dZ34 = Z3_enc_value - Z4_enc_value; // НАХОДИМ РАЗНОСТЬ 3-ОЙ И 4-ОЙ КАРЕТОК
  int dZ12_speed = KpZ12 * dZ12; // УМНОЖАЕМ НА ПРОПОРЦИОНАЛЬНЫЙ КОЭФФИЦЕНТ ДЛЯ КАРЕТОК Z1 И Z2
  int dZ34_speed = KpZ34 * dZ34; // УМНОЖАЕМ НА ПРОПОРЦИОНАЛЬНЫЙ КОЭФФИЦЕНТ ДЛЯ КАРЕТОК Z3 И Z4
  int dZmid_speed = round((dZ12_speed + dZ34_speed) / 2); // НАХОДИ СРЕДНЕЕ ЗАНЧЕНИЕ И ОКРУГЛЯЕМ ЕГО (НЕОБХОДИМО ДЛЯ УРАВНЕНИЯ ПЛАНКИ ОСИ Х)
  int Z1_sp = abs(speed_ar[Z1_arcell] - dZmid_speed); // ВЫЧИТАЕМ ИЗ УСТАНВЛОЕННОЙ СКОРОСТИ ДЛЯ КАРЕТКИ Z1 И ДЕЛАЕМ АБСОЛЮТНЫМ (ПО МОДУЛЮ)
  int Z2_sp = abs(speed_ar[Z2_arcell] + dZmid_speed); // ВЫЧИТАЕМ ИЗ УСТАНВЛОЕННОЙ СКОРОСТИ ДЛЯ КАРЕТКИ Z2 И ДЕЛАЕМ АБСОЛЮТНЫМ (ПО МОДУЛЮ)
  int Z3_sp = abs(speed_ar[Z3_arcell] - dZmid_speed); // ВЫЧИТАЕМ ИЗ УСТАНВЛОЕННОЙ СКОРОСТИ ДЛЯ КАРЕТКИ Z3 И ДЕЛАЕМ АБСОЛЮТНЫМ (ПО МОДУЛЮ)
  int Z4_sp = abs(speed_ar[Z4_arcell] + dZmid_speed); // ВЫЧИТАЕМ ИЗ УСТАНВЛОЕННОЙ СКОРОСТИ ДЛЯ КАРЕТКИ Z4 И ДЕЛАЕМ АБСОЛЮТНЫМ (ПО МОДУЛЮ)
  Z1_sp = constrain (Z1_sp, 0, 1020); // ОГРАНИЧИВАЕМ НУЖНУЮ СКОРСТЬ В ПРЕДЕЛАХ МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ ДЛЯ КАРЕТКИ Z1
  Z2_sp = constrain (Z2_sp, 0, 1020); // ОГРАНИЧИВАЕМ НУЖНУЮ СКОРСТЬ В ПРЕДЕЛАХ МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ ДЛЯ КАРЕТКИ Z2
  Z3_sp = constrain (Z3_sp, 0, 1020); // ОГРАНИЧИВАЕМ НУЖНУЮ СКОРСТЬ В ПРЕДЕЛАХ МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ ДЛЯ КАРЕТКИ Z3
  Z4_sp = constrain (Z4_sp, 0, 1020); // ОГРАНИЧИВАЕМ НУЖНУЮ СКОРСТЬ В ПРЕДЕЛАХ МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ ДЛЯ КАРЕТКИ Z4

  switch(mode) // СМОТРИМ КАКОЙ РЕЖИМ У НАС ПРОСЯТ
  {
    case move_up: // ЕДЕМ ВПЕРЕД (В СТОРОНУ УВЕЛЕЧЕНИЯ КООРДИНАТЫ)
      if (on1 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ  
        Dynamixel.turn(dyn_id_ar[Z1_arcell], RIGHT, Z1_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z1_arcell], RIGHT, 0);

      if (on2 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z2_arcell], LEFT, Z2_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z2_arcell], LEFT, 0);

      if (on3 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z3_arcell], RIGHT, Z3_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z3_arcell], RIGHT, 0);
      
      if (on4 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z4_arcell], LEFT, Z4_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z4_arcell], LEFT, 0);
    break;
    case move_stop: //ПОЛНЫЙ СТОП!!!!
      Dynamixel.turn(dyn_id_ar[Z1_arcell], RIGHT, 0);
      Dynamixel.turn(dyn_id_ar[Z2_arcell], LEFT, 0);
      Dynamixel.turn(dyn_id_ar[Z3_arcell], RIGHT, 0);
      Dynamixel.turn(dyn_id_ar[Z4_arcell], LEFT, 0);

    break;
    case move_down: // ЕДЕМ НАЗАД (В СТОРОНУ УМЕНЬШЕНИЯ КООРДИНАТЫ)
      if (on1 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z1_arcell], LEFT, Z1_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z1_arcell], LEFT, 0);
      
      if (on2 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z2_arcell], LEFT, Z2_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z2_arcell], LEFT, 0);

      if (on3 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z3_arcell], LEFT, Z3_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z3_arcell], LEFT, 0);

      if (on4 == true) // ЕСЛИ ЕСТЬ РАЗРЕШЕНИЕ ДВИГАТЬСЯ ТО ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z4_arcell], LEFT, Z4_sp);
      else // ИНАЧЕ НЕ ДВИГАЕМСЯ
        Dynamixel.turn(dyn_id_ar[Z4_arcell], LEFT, 0);
    break;
  }  
}

void move_Y(int mode = 0) // ФУНКЦИЯ ПЕРЕМЕЩЕНИЯ ОСИ Y
{
  switch(mode) // СМОТРИМ КАКОЙ РЕЖИМ У НАС ПРОСЯТ
  {
    case move_up: // ЕДЕМ ВПЕРЕД (В СТОРОНУ УВЕЛЕЧЕНИЯ КООРДИНАТЫ)
      Dynamixel.turn(dyn_id_ar[Y_arcell], RIGHT, speed_ar[Y_arcell]);
    break;
    case move_stop: //ПОЛНЫЙ СТОП!!!!
      Dynamixel.turn(dyn_id_ar[Y_arcell], RIGHT, 0);
    break;
    case move_down: // ЕДЕМ НАЗАД (В СТОРОНУ УМЕНЬШЕНИЯ КООРДИНАТЫ)
      Dynamixel.turn(dyn_id_ar[Y_arcell], LEFT, speed_ar[Y_arcell]);
    break;
  }
}

bool go_home()
{
  while(endstop_read[Z1_arcell] != true && endstop_read[Z2_arcell] != true && endstop_read[Z3_arcell] != true && endstop_read[Z4_arcell] != true)
  {
    read_endstops();
    move_Z(move_up, !endstop_read[Z1_arcell], !endstop_read[Z2_arcell], !endstop_read[Z3_arcell], !endstop_read[Z4_arcell] );
  }
  move_Z(move_stop, 0, 0, 0, 0);

  while (endstop_read[X1_arcell] != true && endstop_read[X2_arcell])
  {
    read_endstops();
    move_X(move_down, !endstop_read[X1_arcell], !endstop_read[X1_arcell]);
  }
  move_X(move_stop, 0, 0);

  while(endstop_read[Y_arcell] != true)
  {
    read_endstops();
    move_Y(move_down);
  }
  move_Y(move_stop);

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Z1_counter() // СЧЕТЧИК ОСИ Z1
{
  Z1_enc_value++;
}

void Z2_counter() // СЧЕТЧИК ОСИ Z2
{
  Z2_enc_value++;
}

void Z3_counter() // СЧЕТЧИК ОСИ Z3
{
  Z3_enc_value++;
}

void Z4_counter() // СЧЕТЧИК ОСИ Z4
{
  Z4_enc_value++;
}

void X1_counter() // СЧЕТЧИК ОСИ X1
{
  X1_enc_value++;
}

void X2_counter() // СЧЕТЧИК ОСИ X2
{
  X2_enc_value++;
}

void Y_counter() // СЧЕТЧИК ОСИ Y
{
  Y_enc_value++;
}
