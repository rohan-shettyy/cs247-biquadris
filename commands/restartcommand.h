#ifndef RESTARTCOMMAND_H
#define RESTARTCOMMAND_H

#include "command.h"

class RestartCommand : public Command
{
public:
    RestartCommand();
    void Call(Board &board, string file = "") override;
};

#endif
