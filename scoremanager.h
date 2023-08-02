#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

using namespace std;

class ScoreManager
{
    int score;

public:
    static int hiScore;

    ScoreManager();

    void update(int, int, int);

    const int GetScore() const;
    const int GetHighScore() const;
};

#endif
