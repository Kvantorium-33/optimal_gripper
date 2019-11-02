#ifndef AXIS_H
#define AXIS_H
#include <Arduino.h>


    class Axis
    {
    private:
        uint8_t _id = 0;
        uint8_t _endstop_pin = 0;
        uint8_t _encoder_pin = 0;
       
        bool _endstop_mode = false;
        bool _endstop_status = false;
        uint8_t _encoder_value =0;
    public:
        Axis();
        void Ainit(uint8_t _id_,uint8_t _endstop_pin_, uint8_t _encoder_pin_);
        bool endstop_check();
        uint8_t encoder_counter();
        void reload();
    
    };
    #define NORMAL false
    #define INTERR true
    
    

#endif