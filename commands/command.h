#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <memory>

using namespace std;

class Board;

class Command
{
protected:
    string fullcommand;
    string mincommand;
public:
    Command();
    void ComputeMinCommand(Command* other);
    virtual void Call(Board &board) = 0;
    bool CheckCommand(string command);
};

#endif
