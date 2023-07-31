#include <iostream>

#include "../biquadrisgame.h"
#include "../board.h"

#include "blockcommand.h"

using namespace std;

BlockCommand::BlockCommand(char type) : type{type}
{
    fullcommand = type;
    mincommand = type;
}

void BlockCommand::Call(Board &board)
{
    Block newBlock{type, board.GetLevel()};
    pair<int,int> shift = make_pair(board.GetCurrBlock().getLeft().first - newBlock.getLeft().first, board.GetCurrBlock().getLeft().second - newBlock.getLeft().second);
    newBlock.ShiftCoords(shift.first, shift.second);
    while (board.GetCurrBlock().orientation != newBlock.orientation)
    {
        newBlock.rotate(true, board);
    }
    const vector<pair<int,int>>& coords = newBlock.getCoords();
    if (newBlock.checkBoard(coords, board) && newBlock.checkBounds(coords))
    {
        swap(board.GetCurrBlock(), newBlock);
    }
    else
    {
        cout << "Cannot replace block: Invalid location" << endl;
    }
}
