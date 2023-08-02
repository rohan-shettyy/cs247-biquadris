#include "../board.h"

#include "randomcommand.h"

using namespace std;

RandomCommand::RandomCommand()
{
    fullcommand = "random";
    mincommand = "r";
}

void RandomCommand::Call(Board &board)
{
    board.SetNoRandom(false);
}

