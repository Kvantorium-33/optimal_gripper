#ifndef MATHEMATICS_H
#define MATHEMATICS_H

    class Mathematics
    {
    private:
        int  _wheelD = 0;
        int  _wheelT = 0;
        float _wheelR = 0;
        int  _ws_size[3];
        int  _cell_size[3];

        int  DeltaCor = 0;
        int  DeltaCor_Long[3];
        int  DeltaCor_Turns[3];
        int  DeltaCor_Ticks[3];

        const int  _X_ = 0;
        const int  _Y_ = 1;
        const int  _Z_ = 2;


    public:
        Mathematics();
        void setWheelDeametr(int  wD = 0);
        void setWheelTiks(int  wT = 0);
        void putWSs(int  wsX, int  wsY, int  wsZ);
        void puCells(int  cX, int  cY, int  cZ);
        int  getTicks(int  chooseA, int  nextCor, int  lastCor);

    };
    


#endif