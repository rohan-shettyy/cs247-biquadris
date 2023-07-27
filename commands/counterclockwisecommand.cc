#include "counterclockwisecommand.h"

#include <iostream>

using namespace std;

CounterclockwiseCommand::CounterclockwiseCommand()
{
    fullcommand = "counterclockwise";
    mincommand = "c";
}

void CounterclockwiseCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
