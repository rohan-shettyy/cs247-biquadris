#include <iostream>
#include <memory>
#include "../biquadrisgame.h"
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
    pair<int, int> scoreData = board.UpdateFilledRows();
    board.UpdateScore(scoreData.first, scoreData.second);
    if (scoreData.first == 0 && board.GetLevel() == 4)
    {
        board.CheckAddAsteriskBlock(false);
    }
    else
    {
        board.CheckAddAsteriskBlock(true);
        if (scoreData.first >= 2)
        {
            cout << "Enter a debuff to apply to the other player: " << endl;
            string debuff;
            board.GetGame().GetInputStream() >> debuff;
            Board& otherBoard = board.GetGame().GetOtherBoard(board);
            if (debuff == "blind")
            {
                otherBoard.isBlinded = true;
            }
            else if (debuff == "heavy")
            {
                otherBoard.isHeavy = true;
            }
            else if (debuff == "force")
            {
                char type;
                board.GetGame().GetInputStream() >> type;
                board.GetGame().cmdManager->CallCommand(otherBoard, string{type});
                if (otherBoard.GetCurrBlock().GetType() != type)
                {
                    board.GetGame().Terminate(otherBoard);
                }
            }
        }
    }
    board.isBlinded = false;
    board.turnInProgress = false;
    board.UpdateNextBlock();
}

