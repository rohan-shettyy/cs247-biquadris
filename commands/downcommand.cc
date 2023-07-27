#include "downcommand.h"

#include <iostream>

using namespace std;

DownCommand::DownCommand()
{
    fullcommand = "down";
    mincommand = "d";
}

void DownCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
