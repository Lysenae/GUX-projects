#ifndef PEXESO_H
#define PEXESO_H

#include <QMainWindow>
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "newgamedialog.h"
#include "tile.h"
#include "players.h"
#include "dimension.h"
#include "theme.h"
#include "random.h"


class Pexeso : public QMainWindow
{
    Q_OBJECT

public:
    Pexeso(QWidget *parent = 0);
    ~Pexeso();

private:
    const int nWidth  = 350;
    const int nHeight = 250;

    NewGameDialog *m_ngd;

    Players   *m_players;
    Theme     *m_theme;
    Dimension *m_dim;

    QMenu *m_game_menu;

    QAction *m_new_action;
    QAction *m_save_action;
    QAction *m_load_action;
    QAction *m_quit_action;

    void createMenu();

private slots:
    void getSettings(int players, int theme, QPoint size);
    void onNewGame();
    void onSaveGame();
    void onLoadGame();
};

#endif // PEXESO_H
