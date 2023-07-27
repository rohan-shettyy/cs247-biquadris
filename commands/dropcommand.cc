#include "dropcommand.h"

#include <iostream>

using namespace std;

DropCommand::DropCommand()
{
    fullcommand = "drop";
    mincommand = "d";
}

void DropCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
