#ifndef RIGHTCOMMAND_H
#define RIGHTCOMMAND_H

#include "command.h"

class RightCommand : public Command
{
public:
    RightCommand();
    void Call(Board &board) override;
};

#endif
