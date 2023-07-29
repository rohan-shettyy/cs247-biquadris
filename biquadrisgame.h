#ifndef BIQUADRISGAME_H
#define BIQUADRISGAME_H

#include "board.h"
#include "commands/commandmanager.h"

class BiquadrisGame
{
    bool gameInProgress = false;
public:
    unique_ptr<Board> p1board;
    unique_ptr<Board> p2board;
    unique_ptr<CommandManager> cmdManager;

    bool p1turn;

    BiquadrisGame();

    void Init();
    void Restart();
    void Terminate();
    void TakeTurn();
    void Print();
};

#endif
