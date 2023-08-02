#include <vector>
#include <utility>
#include <iostream>
#include "window.h"
#include "board.h"
#include "graphics.h"

using namespace std;

Graphics::Graphics() : w{780, 500} {}

void Graphics::Render(Board &p1board, Board &p2board)
{
    w.drawScreen(p1board, p2board);
}