#ifndef CLOCKWISECOMMAND_H
#define CLOCKWISECOMMAND_H

#include "command.h"

class ClockwiseCommand : public Command
{
public:
    ClockwiseCommand();
    void Call(Board &board) override;
};

#endif

