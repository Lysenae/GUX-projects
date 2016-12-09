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
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "newgamedialog.h"
#include "tile.h"
#include "players.h"
#include "dimension.h"
#include "theme.h"
#include "board.h"


class Pexeso : public QMainWindow
{
    Q_OBJECT

public:
    Pexeso(QWidget *parent = 0);
    ~Pexeso();

private:
    const int nWidth  = 800;
    const int nHeight = 600;

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

    QWidget *m_info_w;
    QWidget *m_info_w_main;
    QWidget *m_scores_w;
    QWidget *m_window;

    Board *m_board_w;

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
    void createBoard();
    void clearLayout();
    void createNewGame();

    void save(QFile *file);
    bool load(QStringList lines);
    QStringList fileToStringList(QFile *file);
    void showErrorMsg(QString msg);

    void mousePressEvent(QMouseEvent e);

private slots:
    void getSettings(int players, int theme, QPoint size);
    void onNewGame();
    bool onSaveGame();
    bool onLoadGame();
    void onEndTurn(bool inc_score);
    void onGameOver();
};

#endif // PEXESO_H
