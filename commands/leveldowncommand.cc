#include "leveldowncommand.h"

#include <iostream>

using namespace std;

LevelDownCommand::LevelDownCommand()
{
    fullcommand = "leveldown";
    mincommand = "l";
}

void LevelDownCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
