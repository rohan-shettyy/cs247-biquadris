#include <memory>
#include "../board.h"

#include "dropcommand.h"

using namespace std;

DropCommand::DropCommand()
{
    fullcommand = "drop";
    mincommand = "d";
}

void DropCommand::Call(Board &board)
{
    board.GetCurrBlock().drop(board);
    board.AddBlock(board.GetCurrBlock());
    board.turnInProgress = false;
    board.UpdateNextBlock();
}
