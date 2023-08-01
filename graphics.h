#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "board.h"
#include "window.h"

class Graphics
{
    Xwindow w;
public:
    Graphics();
    void Render(Board& p1board, Board& p2board);
};

#endif
