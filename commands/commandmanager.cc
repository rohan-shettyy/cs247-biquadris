#include <map>

#include "blockcommand.h"
#include "clockwisecommand.h"
#include "counterclockwisecommand.h"
#include "downcommand.h"
#include "dropcommand.h"
#include "leftcommand.h"
#include "leveldowncommand.h"
#include "levelupcommand.h"
#include "norandomcommand.h"
#include "randomcommand.h"
#include "restartcommand.h"
#include "rightcommand.h"
#include "sequencecommand.h"

#include "commandmanager.h"

#include <iostream>

using namespace std;

CommandManager::CommandManager()
{
    // Add all the commands to the command manager
    AddCommand("left", new LeftCommand());
    AddCommand("right", new RightCommand());
    AddCommand("down", new DownCommand());
    AddCommand("clockwise", new ClockwiseCommand());
    AddCommand("counterclockwise", new CounterclockwiseCommand());
    AddCommand("drop", new DropCommand());
    AddCommand("levelup", new LevelUpCommand());
    AddCommand("leveldown", new LevelDownCommand());
    AddCommand("norandom", new NorandomCommand());
    AddCommand("random", new RandomCommand());
    AddCommand("sequence", new SequenceCommand());
    AddCommand("restart", new RestartCommand());
    AddCommand("I", new BlockCommand('I'));
    AddCommand("J", new BlockCommand('J'));
    AddCommand("L", new BlockCommand('L'));
    AddCommand("S", new BlockCommand('S'));
    AddCommand("Z", new BlockCommand('Z'));
    AddCommand("T", new BlockCommand('T'));
    AddCommand("O", new BlockCommand('O'));
}

void CommandManager::AddCommand(string fullcommand, Command* commandObj)
{
    for (auto cmd : commands)
    {
        cmd.second->ComputeMinCommand(commandObj);
    }

    commands.insert(pair<string, Command*>(fullcommand, commandObj));
}

void CommandManager::CallCommand(Board &board, string command, int multiplicity)
{
    for (auto cmd : commands)
    {
        if (cmd.second->CheckCommand(command))
        {
            for (int i = 0; i < multiplicity; i++)
            {
                cmd.second->Call(board);
            }
            return;
        }
    }
    cout << "Invalid command" << endl;
}
