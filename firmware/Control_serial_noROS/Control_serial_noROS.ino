#include <DynamixelWorkbench.h>
/*Z
   +----------------->Y
   |
   |
   |
   |
   |
   V
   X
 */

// ОСЬ Z /////
#define ZDYN1_ID 1
#define ZDYN2_ID 2
#define ZDYN3_ID 3
#define ZDYN4_ID 4

// ОСЬ X 
#define XDYN1_ID 5
#define XDYN2_ID 6

// ОСЬ Y
#define YDYN_ID  7 

// ЗАХВАТ 
#define GRIP_ID  8
// ПОВОРОТ ЗАХВАТА
#define GRIP_ROT_ID 9

// НАСОС
#define PUMP_PIN 15

// КООРДИНАТЫ
#define cell_Xlenght 100 //длина 1-ой ячейки по оси X в милиметрах
#define cell_Ylenght 100 //длина 1-ой ячейки по оси Y в милиметрах
#define cell_Zlenght 100 //длина 1-ой ячейки по оси Z в милиметрах
#define XLenght 7400 //длина рабочей части оси X в милиметрах
#define YLenght 7400 //длина рабочей части оси Y в милиметрах
#define ZLenght 7400 //длина рабочей части оси Z в милиметрах
float nextX = 0.0;  //значение следующей координаты X
float nextY = 0.0;  //значение следующей координаты Y
float nextZ = 0.0;  //занчение следующей координаты Z
float lastX = 0.0;  //значение предыдущей координаты X
float lastY = 0.0;  //значение предыдущей координаты Y
float lastZ = 0.0;   //значение предыдущей координаты Z

// ЭНКОДЕРЫ
#define ZDYN1_ENC_PIN 0 // пин прерывания энкодера 1 динамикселя оси Z
#define ZDYN2_ENC_PIN 1 // пин прерывания энкодера 2 динамикселя оси Z
#define ZDYN3_ENC_PIN 2 // пин прерывания энкодера 3 динамикселя оси Z
#define ZDYN4_ENC_PIN 3 // пин прерывания энкодера 4 динамикселя оси Z

#define XDYN1_ENC_PIN 4 // пин прерывания энкодера 1 динамикселя оси X
#define XDYN2_ENC_PIN 5 // пин прерывания энкодера 2 динамикселя оси X

#define YDYN_ENC_PIN  6 // пин прерывания энкодера динамикселя оси Y

#define wheel_ticks 65 // количество тиков колеса энкодера на оборот
#define wheel_deametr  30 // диаметр колеса в милиметрах
float wheel_round_L = 0.0; 

int ZDYN1_ENC_VAL = 0; //переменная счетчика 1 энкодера оси Z
int ZDYN2_ENC_VAL = 0; //переменная счетчика 2 энкодера оси Z
int ZDYN3_ENC_VAL = 0; //переменная счетчика 3 энкодера оси Z
int ZDYN4_ENC_VAL = 0; //переменная счетчика 4 энкодера оси Z

int XDYN1_ENC_VAL = 0; //переменная счетчика 1 энкодера оси X
int XDYN2_ENC_VAL = 0; //переменная счетчика 2 энкодера оси X

int YDYN_ENC_VAL = 0; //переменная счетчика энкодера оси Y

DynamixelWorkbench Dxl; //инициализируем шину DXL

void setup()
{
    wheel_round();

}

//функции прерываний энкодеров оси Z
void ZDYN1_ENC_COUNTER(){
    ZDYN1_ENC_VAL++; //первый энкодер Z
}
void ZDYN2_ENC_COUNTER(){
    ZDYN2_ENC_VAL++; //второй энкодер оси Z
}
void ZDYN3_ENC_COUNTER(){
    ZDYN3_ENC_VAL++; //третий энкодер оси Z
}
void ZDYN4_ENC_COUNTER(){
    ZDYN4_ENC_VAL++; //четвертый энкодер оси Z
}
//функции прерываний экодеров оси X
void XDYN1_ENC_COUNTER(){
    XDYN1_ENC_VAL++; 
}
void XDYN2_ENC_COUNTER(){
    XDYN2_ENC_VAL++;
}
//функции прерываний энкодеров оси Y
void YDYN_ENC_COUNTER(){
    YDYN_ENC_VAL++;
}
void wheel_round(){
    wheel_round_L = PI * wheel_deametr;
}

int coord_to_ticks_Axis_Z(int lastZ, int nextZ){
    int dZ = nextZ - lastZ;
    int dlZ = dZ*cell_Zlenght;
    double dobZ = dlZ/ wheel_round_L;
    double tiksZ = dobZ * wheel_ticks;

    return tiksZ;
}
int coord_to_ticks_Axis_X(int lastX, int nextX){
    int dX = nextX - lastX;
    int dlX = dX*cell_Xlenght;
    double dobX = dlX/ wheel_round_L;
    double tiksX = dobX * wheel_ticks;

    return tiksX;
}
int coord_to_ticks_Axis_Y(int lastY, int nextY){
    int dY = nextY - lastY;
    int dlY = dY*cell_Zlenght;
    double dobY = dlY/ wheel_round_L;
    double tiksY = dobY * wheel_ticks;

    return tiksY;
}
void loop()
{

}