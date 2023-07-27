#include "randomcommand.h"

#include <iostream>

using namespace std;

RandomCommand::RandomCommand()
{
    fullcommand = "random";
    mincommand = "r";
}

void RandomCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
