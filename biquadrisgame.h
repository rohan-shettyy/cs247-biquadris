#ifndef BIQUADRISGAME_H
#define BIQUADRISGAME_H

#include "graphics.h"
#include "board.h"
#include "commands/commandmanager.h"

class BiquadrisGame
{
    bool gameInProgress = false;
    bool shouldRestart = false;
    bool useSequence = false;
    
    ifstream& sequenceIn;

    string scriptfile1;
    string scriptfile2;
    int startLevel;
    bool textOnly;

    Graphics graphics;

public:
    unique_ptr<Board> p1board;
    unique_ptr<Board> p2board;
    unique_ptr<CommandManager> cmdManager;

    bool p1turn;

    BiquadrisGame(ifstream& in, string scriptfile1, string scriptfile2, int level, bool textOnly);

    void Init();
    void Restart();
    void Terminate(Board&);
    void TakeTurn();
    void Print();

    void SetGameInProgress(bool inProgress);

    istream& GetInputStream();
    void SetSequence(string filename);
    Board& GetOtherBoard(Board& board);
};

#endif
