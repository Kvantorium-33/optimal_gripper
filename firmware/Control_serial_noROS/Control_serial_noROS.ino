#include <DynamixelWorkbench.h>

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
float nextX = 0.0; //значение следующей координаты X
float nextY = 0.0; //значение следующей координаты Y
float lastX = 0.0; //значение предыдущей координаты X
float lastY = 0.0; //значение предыдущей координаты Y

// ЭНКОДЕРЫ
#define ZDYN1_ENC_PIN 0 // пин прерывания энкодера 1 динамикселя оси Z
#define ZDYN2_ENC_PIN 1 // пин прерывания энкодера 2 динамикселя оси Z
#define ZDYN3_ENC_PIN 2 // пин прерывания энкодера 3 динамикселя оси Z
#define ZDYN4_ENC_PIN 3 // пин прерывания энкодера 4 динамикселя оси Z

#define XDYN1_ENC_PIN 4 // пин прерывания энкодера 1 динамикселя оси X
#define XDYN2_ENC_PIN 5 // пин прерывания энкодера 2 динамикселя оси X

#define YDYN_ENC_PIN  6 // пин прерывания энкодера динамикселя оси Y

int ZDYN1_ENC_VAL = 0;
int ZDYN2_ENC_VAL = 0;
int ZDYN3_ENC_VAL = 0;
int ZDYN4_ENC_VAL = 0;

DynamixelWorkbench Dxl;

void setup()
{

}

void loop()
{

}