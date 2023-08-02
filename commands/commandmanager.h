#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <string>
#include <map>
#include <memory>

#include "command.h"

using namespace std;

class Board;

class CommandManager
{
    map<string, unique_ptr<Command>> commands;

public:
    CommandManager();
    void CallCommand(Board &board, string command, int multiplicity = 1);
    void AddCommand(string fullcommand, Command* commandObj);
};
#endif

