// File:   main.cpp
// Author: Daniel Klimaj; xklima22@stud.fit.vutbr.cz

#include "pexeso.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pexeso w;
    w.show();

    return a.exec();
}
