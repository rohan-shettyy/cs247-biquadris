#include "command.h"

Command::Command() : fullcommand{""}, mincommand{""} {}

void Command::ComputeMinCommand(Command* other)
{
    Command* larger = (this->fullcommand.size() > other->fullcommand.size()) ? this : other;
    Command* smaller = (this->fullcommand.size() > other->fullcommand.size()) ? other : this;

    for (int i = 0; i < (int)smaller->fullcommand.size(); i++)
    {
        if (larger->fullcommand[i] != smaller->fullcommand[i])
        {
            if (i >= (int)smaller->mincommand.size())
            {
                smaller->mincommand = smaller->fullcommand.substr(0, i + 1);
            }
            if (i >= (int)larger->mincommand.size())
            {
                larger->mincommand = larger->fullcommand.substr(0, i + 1);
            }

            break;
        }
    }

    if (smaller->fullcommand == larger->fullcommand.substr(0, smaller->fullcommand.size()))
    {
        smaller->mincommand = smaller->fullcommand;

        if (larger->mincommand.size() < smaller->mincommand.size() + 1)
        {
            larger->mincommand = larger->fullcommand.substr(0, smaller->fullcommand.size() + 1);
        }
    }
}

bool Command::CheckCommand(string command)
{
    if (fullcommand.substr(0, command.size()) == command && command.substr(0, mincommand.size()) == mincommand)
    {
        return true;
    }
    
    return false;
}
