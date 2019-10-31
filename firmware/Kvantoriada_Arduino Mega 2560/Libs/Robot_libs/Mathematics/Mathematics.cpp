#include "Mathematics.h"

Mathematics::Mathematics()
{

};

void Mathematics::setWheelDeametr(uint8_t wD = 0)
{
    _wheelD = wD;
    _wheelR = _wheelD * PI;
};
void Mathematics::setWheelTiks(uint8_t wT = 0)
{
    _wheelT = wT;
};

void Mathematics::putWSs(uint8_t wsX, uint8_t wsY, uint8_t wsZ)
{
    _ws_size[_X_] = wsX;
    _ws_size[_Y_] = wsY;
    _ws_size[_Z_] = wsZ;
};

void Mathematics::puCells(uint8_t cX, uint8_t cY, uint8_t cZ)
{
    _cell_size[_X_] = cX;
    _cell_size[_Y_] = cY;
    _cell_size[_Z_] = cZ;

}

uint8_t Mathematics::getTicks(uint8_t chooseA, uint8_t nextCor, uint8_t lastCor)
{   DeltaCor = lastCor - nextCor;

    switch(chooseA)
    {
        case   0:
            DeltaCor_Long[_X_] = DeltaCor * _cell_size[_X_];
            DeltaCor_Turns[_X_] = DeltaCor_Long[_X_] / _wheelD;
            DeltaCor_Ticks[_X_] = DeltaCor_Turns[_X_] * _wheelT;

            return DeltaCor_Ticks[_X_];
            break;

         case   1:
            DeltaCor_Long[_Y_] = DeltaCor * _cell_size[_Y_];
            DeltaCor_Turns[_Y_] = DeltaCor_Long[_Y_] / _wheelD;
            DeltaCor_Ticks[_Y_] = DeltaCor_Turns[_Y_] * _wheelT;

            return DeltaCor_Ticks[_Y_];
            break;

        case   2:
            DeltaCor_Long[_Z_] = DeltaCor * _cell_size[_Z_];
            DeltaCor_Turns[_Z_] = DeltaCor_Long[_Z_] / _wheelD;
            DeltaCor_Ticks[_Z_] = DeltaCor_Turns[_Z_] * _wheelT;

            return DeltaCor_Ticks[_Z_];
            break;       
    }
}