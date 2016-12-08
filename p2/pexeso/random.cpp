#include "random.h"

void Random::shuffle(QVector<int> *in)
{
    int i = in->size();
    int j, t;
    while(i > 1)
    {
        i = i - 1;
        qsrand(QTime::currentTime().msec());
        j = qrand() % i;
        t = in->at(i);
        in->replace(i, in->at(j));
        in->replace(j, t);
    }
}
