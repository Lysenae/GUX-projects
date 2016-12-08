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
        int tmp = m_scores[i];
        m_scores.replace(i, tmp);
    }
}
