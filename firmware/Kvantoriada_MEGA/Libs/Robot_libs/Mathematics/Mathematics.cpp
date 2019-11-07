#include "Mathematics.h"

Mathematics::Mathematics()
{

};

void Mathematics::setWheelDeametr(int  wD = 0)
{
    _wheelD = wD;
    _wheelR = _wheelD * 3.14;
};
void Mathematics::setWheelTiks(int  wT = 0)
{
    _wheelT = wT;
};

void Mathematics::putWSs(int  wsX, int  wsY, int  wsZ)
{
    _ws_size[_X_] = wsX;
    _ws_size[_Y_] = wsY;
    _ws_size[_Z_] = wsZ;
};

void Mathematics::puCells(int  cX, int  cY, int  cZ)
{
    _cell_size[_X_] = cX;
    _cell_size[_Y_] = cY;
    _cell_size[_Z_] = cZ;

}

int  Mathematics::getTicks(int  chooseA, int  nextCor, int  lastCor)
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