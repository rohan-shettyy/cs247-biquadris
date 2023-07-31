#ifndef SEQUENCECOMMAND_H
#define SEQUENCECOMMAND_H

#include "command.h"

class SequenceCommand : public Command
{
public:
    SequenceCommand();
    void Call(Board &board) override;
};

#endif
