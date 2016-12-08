#ifndef PLAYER_H
#define PLAYER_H


class Players
{
public:
    Players();
    void setCount(int count);
    void next();
    int current();
    int count();

private:
    int m_count;
    int m_current;
};

#endif // PLAYER_H
