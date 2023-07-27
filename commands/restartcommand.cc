#include "restartcommand.h"

#include <iostream>

using namespace std;

RestartCommand::RestartCommand()
{
    fullcommand = "restart";
    mincommand = "r";
}

void RestartCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
