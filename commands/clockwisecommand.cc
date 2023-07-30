#include "../board.h"

#include "clockwisecommand.h"

using namespace std;

ClockwiseCommand::ClockwiseCommand()
{
    fullcommand = "clockwise";
    mincommand = "c";
}

void ClockwiseCommand::Call(Board &board, string file)
{
    board.GetCurrBlock().rotate(true);
}
