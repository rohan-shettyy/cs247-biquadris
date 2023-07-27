#include "clockwisecommand.h"

#include <iostream>

using namespace std;

ClockwiseCommand::ClockwiseCommand()
{
    fullcommand = "clockwise";
    mincommand = "c";
}

void ClockwiseCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
