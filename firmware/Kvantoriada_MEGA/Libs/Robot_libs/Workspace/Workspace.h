#ifndef WORKSPACE_H
#define WORKSPACE_H

class Workspace
{
private:
    uint8_t _cell_X_size, _cell_Y_size, _cell_Z_size;
    uint8_t _ws_X_size, _ws_Y_size, _ws_Z_size;
    
public:
    Workspace();
    void set_cell_size(uint8_t _cell_X_size_, uint8_t _cell_Y_size_, uint8_t _cell_Z_size_);
    void set_ws_size(uint8_t _ws_X_size_, uint8_t _ws_Y_size_, uint8_t _ws_Z_size_);
    uint8_t put_Cell_Size(char Cell_Axis);
    uint8_t put_WS_Size(char WS_Axis);

};

#endif
