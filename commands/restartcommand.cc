#include "../biquadrisgame.h"
#include "../board.h"

#include "restartcommand.h"

using namespace std;

RestartCommand::RestartCommand()
{
    fullcommand = "restart";
    mincommand = "r";
}

void RestartCommand::Call(Board &board)
{
    board.GetGame().Restart();
}

