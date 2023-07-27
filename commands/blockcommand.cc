#include "blockcommand.h"

#include <iostream>

using namespace std;

BlockCommand::BlockCommand(char type) : type{type}
{
    fullcommand = type;
    mincommand = type;
}

void BlockCommand::Call(Board &board, string file = "")
{
    cout << mincommand << endl;
}
