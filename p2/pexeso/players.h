#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>

class Players
{
public:
    Players();
    void setCount(int count);
    void next();
    int current();
    int count();
    int getScore(int i);
    void incScore(int i);

private:
    int m_count;
    int m_current;

    QVector<int> m_scores;
};

#endif // PLAYER_H
