#include <iostream>
#include <fstream>

#include "../biquadrisgame.h"
#include "../board.h"

#include "sequencecommand.h"

using namespace std;

SequenceCommand::SequenceCommand()
{
    fullcommand = "sequence";
    mincommand = "s";
}

void SequenceCommand::Call(Board &board)
{
    string filename;
    board.GetGame().GetInputStream() >> filename;

    board.GetGame().SetSequence(filename);
}

