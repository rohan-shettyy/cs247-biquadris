#include "../board.h"

#include "downcommand.h"

using namespace std;

DownCommand::DownCommand()
{
    fullcommand = "down";
    mincommand = "d";
}

void DownCommand::Call(Board &board)
{
    board.GetCurrBlock().shift('d', board);
}

