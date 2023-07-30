#include "scoremanager.h"

ScoreManager::ScoreManager() : score{0} {}

void ScoreManager::update(int level, int rowsCleared)
{
    //score += (level + rowsCleared) * (level + rowsCleared);
}

const int ScoreManager::GetScore() const
{
    return score;
}

int ScoreManager::hiScore = 0;