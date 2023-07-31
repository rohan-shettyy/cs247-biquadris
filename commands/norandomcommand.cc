#include <iostream>

#include "../biquadrisgame.h"
#include "../board.h"

#include "norandomcommand.h"

using namespace std;

NorandomCommand::NorandomCommand()
{
    fullcommand = "norandom";
    mincommand = "n";
}

void NorandomCommand::Call(Board &board)
{
    string file;
    board.GetGame().GetInputStream() >> file;
    board.SetNoRandom(true, file);
}
