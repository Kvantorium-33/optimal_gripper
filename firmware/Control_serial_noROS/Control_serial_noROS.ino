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

// НАСОС
#define PUMP_PIN 10

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
    ZDYN3_ENC_VAL++; //третий энкодра оси Z
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
void coordinates_to_ticks_and_goto(int nextX, int nextY){
    int dX = 0; // дельта X
    int dY = 0; // дельта Y
    int dZ = 0; // дельта Z
    float dlX = 0.0; // длина дельта X в милиметрах
    float dlY = 0.0; // длина дельта Y в милиметрах
    float dlZ = 0.0; // длина дельта Z в милиметрах
    float obX = 0.0; // количество оборотов по оси Z
    float obY = 0.0; // количество оборотов по оси Y
    float obZ = 0.0; // количество оборотов по оси Z
    double tiksX = 0;
    double tiksY = 0;
    double tiksZ = 0;

    dX = max(nextX,lastX) - min(nextX,lastX); //расчет дельта X
    dY = max(nextY,lastY) - min(nextY,lastY); //расчет дельта Y
    dZ = max(nextZ,lastZ) - min(nextZ,lastZ); //расчет дельта Z

    lastX = nextX;
    lastY = nextY;
    lastZ = nextZ;
    dlX = dX * cell_Xlenght; // расчет длины дельта X в милиметрах
    dlY = dY * cell_Ylenght; // расчет длины дельта Y в милиметрах
    dlZ = dZ * cell_Zlenght; // расчет длины дельта Z в милиметрах 

    obX = dlX / wheel_round_L;
    obY = dlY / wheel_round_L;
    obZ = dlZ / wheel_round_L;

    tiksX = obX * wheel_ticks;
    tiksY = obY * wheel_ticks;
    tiksZ = obZ * wheel_ticks;
}
void go_to_coorinates(double tiksX, double tiksY, double tiksZ, int speed){
    bool x_dir_rev = false;
    bool y_dir_rev = false;
    bool z_dir_rev = false;
    if (nextX > lastY)
        x_dir_rev = false;
    else 
        x_dir_rev = true;

    if (nextY > lastY)
        y_dir_rev = false;
    else 
        y_dir_rev = true;

    if (nextZ > lastZ)
        z_dir_rev = false;
    else 
        z_dir_rev = true;
    
    

}
void loop()
{

}