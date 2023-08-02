#include <map>

#include "../biquadrisgame.h"
#include "blockcommand.h"
#include "../board.h"
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
#include <memory>

using namespace std;

CommandManager::CommandManager()
{
    // Add all the commands to the command manager

    Command* cmd = new LeftCommand();
    AddCommand("left", cmd);
    cmd = new RightCommand();
    AddCommand("right", cmd);
    cmd = new DownCommand();
    AddCommand("down", cmd);
    cmd = new ClockwiseCommand();
    AddCommand("clockwise", cmd);
    cmd = new CounterclockwiseCommand();
    AddCommand("counterclockwise", cmd);
    cmd = new DropCommand();
    AddCommand("drop", cmd);
    cmd = new LevelUpCommand();
    AddCommand("levelup", cmd);
    cmd = new LevelDownCommand();
    AddCommand("leveldown", cmd);
    cmd = new NorandomCommand();
    AddCommand("norandom", cmd);
    cmd = new RandomCommand();
    AddCommand("random", cmd);
    cmd = new SequenceCommand();
    AddCommand("sequence", cmd);
    cmd = new RestartCommand();
    AddCommand("restart", cmd);
    cmd = new BlockCommand('I');
    AddCommand("I", cmd);
    cmd = new BlockCommand('J');
    AddCommand("J", cmd);
    cmd = new BlockCommand('L');
    AddCommand("L", cmd);
    cmd = new BlockCommand('S');
    AddCommand("S", cmd);
    cmd = new BlockCommand('Z');
    AddCommand("Z", cmd);
    cmd = new BlockCommand('T');
    AddCommand("T", cmd);
    cmd = new BlockCommand('O');
    AddCommand("O", cmd);
}

void CommandManager::AddCommand(string fullcommand, Command* commandObj)
{
    for (auto& cmd : commands)
    {
        cmd.second->ComputeMinCommand(commandObj);
    }

    commands.insert(make_pair(fullcommand, unique_ptr<Command>(commandObj)));
}

void CommandManager::CallCommand(Board &board, string command, int multiplicity)
{
    for (auto& cmd : commands)
    {
        if (cmd.second->CheckCommand(command))
        {
            for (int i = 0; i < multiplicity; i++)
            {
                cmd.second->Call(board);
            }
            if (cmd.first == "left" || cmd.first == "right" || cmd.first == "clockwise" || cmd.first == "counterclockwise")
            {
                if (board.isHeavy)
                {
                    if (cmd.first == "left" || cmd.first == "right")
                    {
                        pair<int, int> currLeft = board.GetCurrBlock().getLeft();
                        board.GetCurrBlock().shift('d', board);
                        board.GetCurrBlock().shift('d', board);
                        if (board.GetCurrBlock().getLeft().first - currLeft.first < 2)
                        {
                            board.GetGame().cmdManager->CallCommand(board, "drop");
                        }
                        return;
                    }
                }
                if (board.GetLevel() >= 3)
                {
                    board.GetCurrBlock().shift('d', board);
                    return;
                }
            }
            return;
        }
    }
    cout << "Invalid command" << endl;
}

