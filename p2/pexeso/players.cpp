#include "players.h"

Players::Players()
{
    m_count   = 1;
    m_current = 1;
}

void Players::setCount(int count)
{
    if(count < 1 || count > 4)
        m_count = 1;
    else
        m_count = count;
    m_current = 1;
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
