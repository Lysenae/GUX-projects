#ifndef PEXESO_H
#define PEXESO_H

#include <QMainWindow>

#include "newgamedialog.h"
#include "tile.h"
#include "players.h"
#include "dimension.h"
#include "theme.h"


class Pexeso : public QMainWindow
{
    Q_OBJECT

public:
    Pexeso(QWidget *parent = 0);
    ~Pexeso();

private:
    NewGameDialog *m_ngd;

    Players   *m_players;
    Theme     *m_theme;
    Dimension *m_dim;

private slots:
    void getSettings(int players, int theme, QPoint size);
};

#endif // PEXESO_H
