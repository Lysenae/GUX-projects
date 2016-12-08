#ifndef SHUFFLE_H
#define SHUFFLE_H

#include <QVector>
#include <QtGlobal>
#include <QTime>

#include <QDebug>

class Random
{
public:
    static void shuffle(QVector<int> *in);
};

#endif // SHUFFLE_H
