#include "../board.h"

#include "leftcommand.h"

using namespace std;

LeftCommand::LeftCommand()
{
    fullcommand = "left";
    mincommand = "l";
}

void LeftCommand::Call(Board &board, string file)
{
    board.GetCurrBlock().shift('l', board);
}
