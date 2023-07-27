#include "levelupcommand.h"

#include <iostream>

using namespace std;

LevelUpCommand::LevelUpCommand()
{
    fullcommand = "levelup";
    mincommand = "l";
}

void LevelUpCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
