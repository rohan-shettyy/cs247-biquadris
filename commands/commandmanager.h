#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <string>
#include <map>

using namespace std;

class Board;
class Command;

class CommandManager
{
    map<string, Command*> commands;

public:
    CommandManager();
    void CallCommand(Board &board, string command, int multiplicity = 1);
    void AddCommand(string fullcommand, Command* commandObj);
};
#endif
