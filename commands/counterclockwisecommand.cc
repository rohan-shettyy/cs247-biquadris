#include "../board.h"

#include "counterclockwisecommand.h"

using namespace std;

CounterclockwiseCommand::CounterclockwiseCommand()
{
    fullcommand = "counterclockwise";
    mincommand = "c";
}

void CounterclockwiseCommand::Call(Board &board)
{
    board.GetCurrBlock().rotate(false, board);
}

