#include "rightcommand.h"

#include <iostream>

using namespace std;

RightCommand::RightCommand()
{
    fullcommand = "right";
    mincommand = "r";
}

void RightCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
