#ifndef NORANDOMCOMMAND_H
#define NORANDOMCOMMAND_H

#include "command.h"

class NorandomCommand : public Command
{
public:
    NorandomCommand();
    void Call(Board &board) override;
};

#endif
