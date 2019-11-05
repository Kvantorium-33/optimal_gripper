#include "SConfig.h"
#include "WS_config.h"
#include "Pinout_config.h"

#include <DynamixelSerial3.h>
#define contr_pin 26

Pinout_config PC;
SConfig SC;
#define COM Serial2

#define Axis_arcels 4
#define axis_id 0
#define encoder_pin 1
#define endstop_pin 2
#define encoder_val 3


int Z1[Axis_arcels] = {SC.Z1_id, PC.Z1_encoder_pin, PC.Z1_endstop_pin, 0};
int Z2[Axis_arcels] = {SC.Z2_id, PC.Z2_encoder_pin, PC.Z2_endstop_pin, 0};
int Z3[Axis_arcels] = {SC.Z3_id, PC.Z3_encoder_pin, PC.Z3_endstop_pin, 0};
int Z4[Axis_arcels] = {SC.Z4_id, PC.Z4_encoder_pin, PC.Z4_endstop_pin, 0};

int X1[Axis_arcels] = {SC.X1_id, PC.X1_encoder_pin, PC.X1_endstop_pin, 0};
int X2[Axis_arcels] = {SC.X2_id, PC.X2_encoder_pin, PC.X2_endstop_pin, 0};

int Y[Axis_arcels] = {SC.Y_id, PC.Y_encoder_pin, PC.Y_endstop_pin, 0};

void init_pins()
{
    pinMode(Z1[encoder_pin], INPUT_PULLUP);
    pinMode(Z1[endstop_pin], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Z1[encoder_pin]), Z1_encoder_counter, RISING);

    pinMode(Z2[encoder_pin], INPUT_PULLUP);
    pinMode(Z2[endstop_pin], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Z2[encoder_pin]), Z2_encoder_counter, RISING);

    pinMode(Z3[encoder_pin], INPUT_PULLUP);
    pinMode(Z3[endstop_pin], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Z3[encoder_pin]), Z3_encoder_counter, RISING);

    pinMode(Z4[encoder_pin], INPUT_PULLUP);
    pinMode(Z4[endstop_pin], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Z4[encoder_pin]), Z4_encoder_counter, RISING);

    pinMode(X1[encoder_pin], INPUT_PULLUP);
    pinMode(X1[endstop_pin], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(X1[encoder_pin]), X1_encoder_counter, RISING);

    pinMode(X2[encoder_pin], INPUT_PULLUP);
    pinMode(X2[endstop_pin], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(X2[encoder_pin]), X2_encoder_counter, RISING);

    pinMode(Y[encoder_pin], INPUT_PULLUP);
    pinMode(Y[endstop_pin], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Y[encoder_pin]), Y_encoder_counter, RISING);
}
void dyn_init()
{
    Dynamixel.begin(1000000,contr_pin,contr_pin); 

    delay(1000);
    
    for (int i = 0; i < 10; i++)
    {
        if(Dynamixel.ping(SC.id_ar[i]))
        {
            COM.print("ID: ");
            COM.print(i);
            COM.println(" ping successfully");
        }
        else
        {
            COM.print("ID: ");
            COM.print(i);
            COM.println(" ping FAILED!!!");
        }

        delay(200);  
    }
}
void go_home()
{

}
void go_tuda(int x, int y, int z)
{

}
void init_com()
{
    COM.begin(SC.COM_BAUDRATE);
}
void setup()
{
    init_com();
    init_pins();
    dyn_init();
}
void loop()
{

}

void Z1_encoder_counter()
{
    Z1[encoder_val]+=1;
}

void Z2_encoder_counter()
{
    Z2[encoder_val]+=1;
}

void Z3_encoder_counter()
{
    Z3[encoder_val]+=1;
}

void Z4_encoder_counter()
{
    Z4[encoder_val]+=1;
}

void X1_encoder_counter()
{
    X1[encoder_val]+=1;
}

void X2_encoder_counter()
{
    X2[encoder_val]+=1;
}

void Y_encoder_counter()
{
    Y[encoder_val]+=1;
}

bool Z1_endstop_check()
{
    return digitalRead(Z1[endstop_pin]);
}

bool Z2_endstop_check()
{
    return digitalRead(Z2[endstop_pin]);
}

bool Z3_endstop_check()
{
    return digitalRead(Z3[endstop_pin]);
}

bool Z4_endstop_check()
{
    return digitalRead(Z4[endstop_pin]);
}

bool X1_endstop_check()
{
    return digitalRead(X1[endstop_pin]);
}

bool X2_endstop_check()
{
    return digitalRead(X2[endstop_pin]);
}

bool Y_endstop_check()
{
    return digitalRead(Y[endstop_pin]);
}