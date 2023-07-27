#ifndef COUNTERCLOCKWISECOMMAND_H
#define COUNTERCLOCKWISECOMMAND_H

#include "command.h"

class CounterclockwiseCommand : public Command
{
public:
    CounterclockwiseCommand();
    void Call(Board &board, string file = "") override;
};

#endif
