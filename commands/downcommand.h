#ifndef DOWNCOMMAND_H
#define DOWNCOMMAND_H

#include "command.h"

class DownCommand : public Command
{
public:
    DownCommand();
    void Call(Board &board) override;
};

#endif

