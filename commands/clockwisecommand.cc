#include "../board.h"

#include "clockwisecommand.h"

using namespace std;

ClockwiseCommand::ClockwiseCommand()
{
    fullcommand = "clockwise";
    mincommand = "c";
}

void ClockwiseCommand::Call(Board &board)
{
    board.GetCurrBlock().rotate(true, board);
}
