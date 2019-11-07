#ifndef WORKSPACE_H
#define WORKSPACE_H

class Workspace
{
private:
    int  _cell_X_size, _cell_Y_size, _cell_Z_size;
    int  _ws_X_size, _ws_Y_size, _ws_Z_size;
    
public:
    Workspace();
    void set_cell_size(int  _cell_X_size_, int  _cell_Y_size_, int  _cell_Z_size_);
    void set_ws_size(int  _ws_X_size_, int  _ws_Y_size_, int  _ws_Z_size_);
    int  put_Cell_Size(char Cell_Axis);
    int  put_WS_Size(char WS_Axis);

};

#endif
