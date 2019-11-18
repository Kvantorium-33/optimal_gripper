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

#define Z1_arcell 0
#define Z2_arcell 1
#define Z3_arcell 2
#define Z4_arcell 3

#define X1_arcell 4
#define X2_arcell 5

#define Y_arcell 6

#define Z1_dyn_id 1
#define Z2_dyn_id 2
#define Z3_dyn_id 3
#define Z4_dyn_id 4

#define X1_dyn_id 5
#define X2_dyn_id 6

#define Y_dyn_id 7

#define valve_dyn_id 8
#define rot_grip_dyn_id 9
#define grip_pos_dyn_id 10
const int dyn_id_ar[10] = {
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
                         
#define Z1_encoder_pin  PC15
#define Z2_encoder_pin  PA1
#define Z3_encoder_pin  PC14
#define Z4_encoder_pin  PB13

#define X16_encoder_pin PA3
#define X15_encoder_pin PA2

#define Y_encoder_pin   PA0

#define encoder_count 7
const int encoder_pins_array[7] =   { 

                                        Z1_encoder_pin, 
                                        Z2_encoder_pin, 
                                        Z3_encoder_pin,
                                        Z4_encoder_pin,
                                        X15_encoder_pin, 
                                        X16_encoder_pin, 
                                        Y_encoder_pin

                                    };

#define Z1_endstop_pin  PA6
#define Z2_endstop_pin  PA4
#define Z3_endstop_pin  PB0
#define Z4_endstop_pin  PB1

#define X15_endstop_pin PA5
#define X16_endstop_pin PA7

#define Y_endstop_pin PB14

#define endstop_count 7
bool endstop_read[endstop_count] = {false, false, false, false, false, false, false};

const int endstops_pins_array[endstop_count] =   
                                     { 

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
    Serial.begin(115200);
    
    for (int i = 0; i < encoder_count; i++)
    {
        pinMode(encoder_pins_array[i], INPUT);        
    }
    
    for (int i = 0; i < endstop_count; i++)
    {
        pinMode(endstops_pins_array[i], INPUT);        
    }
    
    
}

void print_encoders()
{
  
}

void print_endstops()
{
  for(int i = 0; i < endstop_count; i++)
  {
    Serial.print(digitalRead(endstops_pins_array[i]) + " ");
  }
  Serial.println();
}

bool read_endstop(int choose = 0)
{ 
  
}
void loop()
{

}
