#include "scoremanager.h"

ScoreManager::ScoreManager() : score{0} {}

void ScoreManager::update(int level, int rowsCleared, int blocksCleared)
{
    int rowScore = (rowsCleared + level) * (rowsCleared + level);
    int bonusPoints = blocksCleared > 0 ? (blocksCleared + 1) * (blocksCleared + 1) : 0;
    score += rowScore + bonusPoints;
}

const int ScoreManager::GetScore() const
{
    return score;
}

int ScoreManager::hiScore = 0;