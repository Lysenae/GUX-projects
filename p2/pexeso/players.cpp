#include "players.h"

Players::Players()
{
    setCount(1);
}

void Players::setCount(int count)
{
    if(count < 1 || count > 4)
        m_count = 1;
    else
        m_count = count;
    m_current = 1;

    m_scores.clear();
    for(int i=0; i<m_count; ++i)
        m_scores.append(0);
}

void Players::next()
{
    m_current = (m_current + 1 > m_count) ? 1 : m_current + 1;
}

int Players::current()
{
    return m_current;
}

int Players::count()
{
    return m_count;
}

int Players::getScore(int i)
{
    i = i-1;
    if(i >=0 && i<m_count)
        return m_scores[i];
    return -1;
}

void Players::incScore(int i)
{
    i = i-1;
    if(i >=0 && i<m_count)
    {
        int tmp = m_scores[i]+1;
        m_scores.replace(i, tmp);
    }
}

void Players::setScore(int i, int score)
{
    i = i-1;
    if(i >=0 && i<m_count)
    {
        m_scores.replace(i, score);
    }
}

QVector<int> Players::getWinners()
{
    QVector<int> w;
    int max = 0;

    for(int i=0; i<m_scores.size(); ++i)
    {
        if(m_scores[i] > max)
            max = m_scores[i];
    }

    for(int i=0; i<m_scores.size(); ++i)
    {
        if(m_scores[i] == max)
            w.append(i+1);
    }

    return w;
}
