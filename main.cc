#include <iostream>

#include "board.h"
#include "commands/commandmanager.h"

using namespace std;

int main(int argc, char** argv)
{
    Board board = Board();

    CommandManager commandManager = CommandManager();

    commandManager.CallCommand(board, "left");
    commandManager.CallCommand(board, "levelup");
    commandManager.CallCommand(board, "L");
    commandManager.CallCommand(board, "ri");
    commandManager.CallCommand(board, "re");
    commandManager.CallCommand(board, "ran");
}
