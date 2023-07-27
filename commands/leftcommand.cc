#include "leftcommand.h"

#include <iostream>

using namespace std;

LeftCommand::LeftCommand()
{
    fullcommand = "left";
    mincommand = "l";
}

void LeftCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
