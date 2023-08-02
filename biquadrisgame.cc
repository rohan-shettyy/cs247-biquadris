#include <iostream>
#include <memory>
#include <sstream>

#include "board.h"
#include "commands/commandmanager.h"

#include "biquadrisgame.h"

using namespace std;

BiquadrisGame::BiquadrisGame(ifstream &in, string scriptfile1, string scriptfile2, int level, bool textOnly) : sequenceIn{in},
                                                                                                               scriptfile1{scriptfile1},
                                                                                                               scriptfile2{scriptfile2},
                                                                                                               startLevel{level},
                                                                                                               textOnly{textOnly},
                                                                                                               graphics{},
                                                                                                               p1board{unique_ptr<Board>(new Board(this, scriptfile1, level))},
                                                                                                               p2board{unique_ptr<Board>(new Board(this, scriptfile2, level))},
                                                                                                               cmdManager{unique_ptr<CommandManager>(new CommandManager())},
                                                                                                               p1turn{true}
{
    ScoreManager::hiScore = 0;
}

void BiquadrisGame::Init()
{
    p1board->Init();
    p2board->Init();
    gameInProgress = true;

    while (gameInProgress)
    {
        TakeTurn();
    }
    if (shouldRestart)
    {
        shouldRestart = false;
        Init();
    }
}

void BiquadrisGame::Restart()
{
    p1board->turnInProgress = false;
    p2board->turnInProgress = false;
    p1board.reset(new Board(this, scriptfile1, startLevel));
    p2board.reset(new Board(this, scriptfile2, startLevel));
    p1turn = false; // will toggle in TakeTurn()
    gameInProgress = false;
    shouldRestart = true;
}

void BiquadrisGame::Terminate(Board &board)
{
    gameInProgress = false;
    if (&board == p1board.get())
    {
        cout << "Player 2 wins!" << endl;
    }
    else
    {
        cout << "Player 1 wins!" << endl;
    }
}

void BiquadrisGame::TakeTurn()
{
    Board *activeBoard = p1board.get();
    if (p1turn)
    {
        cout << "Player 1's turn:" << endl;
    }
    else
    {
        activeBoard = p2board.get();
        cout << "Player 2's turn:" << endl;
    }
    activeBoard->turnInProgress = true;
    while (gameInProgress && activeBoard->turnInProgress)
    {
        Print();
        if (!textOnly)
        {
            // Render
            graphics.Render(*p1board, *p2board);
        }
        string input;
        int mult;
        string command;
        if (!(GetInputStream() >> input))
        {
            gameInProgress = false;
            return;
        }
        istringstream iss{input};
        if (!(iss >> mult))
        {
            mult = 1;
        }
        iss.clear();
        iss >> command;
        cmdManager->CallCommand(*activeBoard, command, mult);
    }
    p1turn = !p1turn;
}

void BiquadrisGame::Print()
{
    const vector<vector<pair<char, shared_ptr<Block>>>> &p1grid = p1board->GetGrid();
    const vector<vector<pair<char, shared_ptr<Block>>>> &p2grid = p2board->GetGrid();

    int high = p1board->GetHighScore();
    for (int j = 0; j < 12 - (int)to_string(high).length(); j++)
    {
        cout << " ";
    }
    cout << "High: ";
    cout << high << endl;

    cout << "Level:    " << p1board->GetLevel() << "      "
         << "Level:    " << p2board->GetLevel() << endl;
    int p1score = p1board->GetScore();
    int p2score = p2board->GetScore();

    cout << "Score:";
    for (int j = 0; j < 5 - (int)to_string(p1score).length(); j++)
    {
        cout << " ";
    }
    cout << p1score << "      ";
    cout << "Score:";
    for (int j = 0; j < 5 - (int)to_string(p2score).length(); j++)
    {
        cout << " ";
    }
    cout << p2score << endl;

    cout << "-----------      -----------" << endl;

    const vector<pair<int, int>> &p1CurrBlock = p1board->GetCurrBlock().getCoords();
    const vector<pair<int, int>> &p2CurrBlock = p2board->GetCurrBlock().getCoords();

    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (p1board->isBlinded && 2 <= j && j <= 8 && 5 <= i && i <= 14)
            {
                cout << "?";
            }
            else
            {
                bool inCurrBlock = false;
                for (auto coord : p1CurrBlock)
                {
                    if (coord.first == i && coord.second == j)
                    {
                        cout << p1board->GetCurrBlock().GetType();
                        inCurrBlock = true;
                    }
                }
                if (!inCurrBlock)
                {
                    cout << p1grid[i][j].first;
                }
            }
        }
        cout << "      ";
        for (int j = 0; j < 11; j++)
        {
            if (p2board->isBlinded && 2 <= j && j <= 8 && 5 <= i && i <= 14)
            {
                cout << "?";
            }
            else
            {
                bool inCurrBlock = false;
                for (auto coord : p2CurrBlock)
                {
                    if (coord.first == i && coord.second == j)
                    {
                        cout << p2board->GetCurrBlock().GetType();
                        inCurrBlock = true;
                    }
                }
                if (!inCurrBlock)
                {
                    cout << p2grid[i][j].first;
                }
            }
        }
        cout << endl;
    }

    cout << "-----------      -----------" << endl;

    const vector<pair<int, int>> &p1NextBlock = p1board->GetNextBlock().getCoords();
    const vector<pair<int, int>> &p2NextBlock = p2board->GetNextBlock().getCoords();
    char p1NextBlockGrid[2][4];
    char p2NextBlockGrid[2][4];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            p1NextBlockGrid[i][j] = ' ';
            p2NextBlockGrid[i][j] = ' ';
        }
    }
    for (auto coord : p1NextBlock)
    {
        p1NextBlockGrid[coord.first - 2][coord.second] = p1board->GetNextBlock().GetType();
    }
    for (auto coord : p2NextBlock)
    {
        p2NextBlockGrid[coord.first - 2][coord.second] = p2board->GetNextBlock().GetType();
    }

    cout << "Next:            Next:" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << p1NextBlockGrid[i][j];
        }
        cout << "             ";
        for (int j = 0; j < 4; j++)
        {
            cout << p2NextBlockGrid[i][j];
        }
        cout << endl;
    }
}

void BiquadrisGame::SetGameInProgress(bool inProgress)
{
    gameInProgress = inProgress;
}

istream &BiquadrisGame::GetInputStream()
{
    if (useSequence)
    {
        return sequenceIn;
    }
    else
    {
        return cin;
    }
}

void BiquadrisGame::SetSequence(string filename)
{
    sequenceIn.close();
    sequenceIn.open(filename);
    useSequence = true;
}

Board &BiquadrisGame::GetOtherBoard(Board &board)
{
    if (&board == p1board.get())
    {
        return *p2board;
    }
    else
    {
        return *p1board;
    }
}
