#ifndef PEXESO_H
#define PEXESO_H

#include <QMainWindow>

#include "newgamedialog.h"

class Pexeso : public QMainWindow
{
    Q_OBJECT

public:
    Pexeso(QWidget *parent = 0);
    ~Pexeso();

private:
    NewGameDialog *m_ngd;

private slots:
    void getSettings(int players, int theme, int size);
};

#endif // PEXESO_H
