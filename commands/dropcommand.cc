#include <iostream>

#include "../board.h"

#include "dropcommand.h"

using namespace std;

DropCommand::DropCommand()
{
    fullcommand = "drop";
    mincommand = "d";
}

void DropCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
    board.turnInProgress = false;
}
