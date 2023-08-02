#include "../board.h"

#include "leveldowncommand.h"

using namespace std;

LevelDownCommand::LevelDownCommand()
{
    fullcommand = "leveldown";
    mincommand = "l";
}

void LevelDownCommand::Call(Board &board)
{
    const int level = board.GetLevel();
    if (level > 0)
    {
        board.SetLevel(level - 1);
    }
}

