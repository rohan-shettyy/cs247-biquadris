#include "../board.h"

#include "levelupcommand.h"

using namespace std;

LevelUpCommand::LevelUpCommand()
{
    fullcommand = "levelup";
    mincommand = "l";
}

void LevelUpCommand::Call(Board &board)
{
    const int level = board.GetLevel();
    if (level < 4)
    {
        board.SetLevel(level + 1);
    }
}

