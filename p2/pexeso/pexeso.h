#ifndef PEXESO_H
#define PEXESO_H

#include <QMainWindow>
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVector>

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

    QHBoxLayout *m_main_lt;
    QVBoxLayout *m_info_lt;
    QHBoxLayout *m_info_lt_main;
    QVBoxLayout *m_info_lt_desc;
    QVBoxLayout *m_info_lt_val;
    QVBoxLayout *m_scores_lt;
    QScrollArea *m_board;
    QWidget *m_info_w;
    QWidget *m_scores_w;
    QWidget *m_window;
    QWidget *m_info_w_main;

    QVBoxLayout *m_rows;
    QVector<QHBoxLayout*> m_cols;

    QLabel *m_players_ld;
    QLabel *m_theme_ld;
    QLabel *m_size_ld;
    QLabel *m_cplayer_ld;
    QLabel *m_players_lv;
    QLabel *m_theme_lv;
    QLabel *m_size_lv;
    QLabel *m_cplayer_lv;
    QVector<QLabel*> m_scores;

    void createMenu();
    void createLayout();
    void clearBoard();
    void createNewGame();

private slots:
    void getSettings(int players, int theme, QPoint size);
    void onNewGame();
    void onSaveGame();
    void onLoadGame();
};

#endif // PEXESO_H
