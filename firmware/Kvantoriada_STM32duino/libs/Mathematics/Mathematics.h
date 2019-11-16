#ifndef MATHEMATICS_H
#define MATHEMATICS_H

    class Mathematics
    {
    private:
        uint8_t _wheelD = 0;
        uint8_t _wheelT = 0;
        float _wheelR = 0;
        uint8_t _ws_size[3];
        uint8_t _cell_size[3];

        uint8_t DeltaCor = 0;
        uint8_t DeltaCor_Long[3];
        uint8_t DeltaCor_Turns[3];
        uint8_t DeltaCor_Ticks[3];

        const uint8_t _X_ = 0;
        const uint8_t _Y_ = 1;
        const uint8_t _Z_ = 2;


    public:
        Mathematics();
        void setWheelDeametr(uint8_t wD = 0);
        void setWheelTiks(uint8_t wT = 0);
        void putWSs(uint8_t wsX, uint8_t wsY, uint8_t wsZ);
        void puCells(uint8_t cX, uint8_t cY, uint8_t cZ);
        uint8_t getTicks(uint8_t chooseA, uint8_t nextCor, uint8_t lastCor);

    };
    


#endif