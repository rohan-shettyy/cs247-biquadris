#include "sequencecommand.h"

#include <iostream>

using namespace std;

SequenceCommand::SequenceCommand()
{
    fullcommand = "sequence";
    mincommand = "s";
}

void SequenceCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
