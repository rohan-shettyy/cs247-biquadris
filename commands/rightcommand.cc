#include "../board.h"

#include "rightcommand.h"

using namespace std;

RightCommand::RightCommand()
{
    fullcommand = "right";
    mincommand = "r";
}

void RightCommand::Call(Board &board)
{
    board.GetCurrBlock().shift('r', board);
}
