#include <iostream>
#include <memory>

#include "board.h"
#include "commands/commandmanager.h"

#include "biquadrisgame.h"

using namespace std;

BiquadrisGame::BiquadrisGame() : p1board{unique_ptr<Board>(new Board())}, p2board{unique_ptr<Board>(new Board())}, cmdManager{unique_ptr<CommandManager>(new CommandManager())}, p1turn{true} {}

void BiquadrisGame::Init()
{
    // p1board->Init();
    // p2board->Init();
    gameInProgress = true;

    while (gameInProgress)
    {
        TakeTurn();
    }
}

void BiquadrisGame::Restart()
{
    // p1board->Restart();
    // p2board->Restart();
}

void BiquadrisGame::Terminate()
{
    // p1board->Terminate();
    // p2board->Terminate();
    gameInProgress = false;
}

void BiquadrisGame::TakeTurn()
{
    Board& activeBoard = *p1board;
    if (p1turn)
    {
        cout << "Player 1's turn:" << endl;
    }
    else
    {
        activeBoard = *p2board;
        cout << "Player 2's turn:" << endl;
    }
    activeBoard.turnInProgress = true;
    while (activeBoard.turnInProgress)
    {
        string command;
        cin >> command;
        cmdManager->CallCommand(activeBoard, command);
    }
    p1turn = !p1turn;
}
