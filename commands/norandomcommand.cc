#include "norandomcommand.h"

#include <iostream>

using namespace std;

NorandomCommand::NorandomCommand()
{
    fullcommand = "norandom";
    mincommand = "n";
}

void NorandomCommand::Call(Board &board, string file)
{
    cout << mincommand << endl;
}
