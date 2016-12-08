#include "pexeso.h"

Pexeso::Pexeso(QWidget *parent) : QMainWindow(parent)
{
    m_ngd = new NewGameDialog();

    m_dim     = new Dimension(0, 0);
    m_players = new Players();
    m_theme   = new Theme();

    QRect scr = QApplication::desktop()->screenGeometry();
    setGeometry(scr.width()/2 - nWidth/2, scr.height()/2 - nHeight/2,
        nWidth, nHeight);
    setWindowTitle(tr("Pexeso"));
    setMinimumSize(nWidth, nHeight);

    createMenu();

    QObject::connect(m_ngd, SIGNAL(passSettings(int, int, QPoint)),
        this, SLOT(getSettings(int, int, QPoint)));
}

Pexeso::~Pexeso()
{
}

void Pexeso::createMenu()
{
    m_new_action = new QAction(tr("&New ..."), this);
    m_new_action->setShortcuts(QKeySequence::New);
    m_new_action->setStatusTip(tr("New game"));
    QObject::connect(m_new_action, SIGNAL(triggered()), this, SLOT(onNewGame()));

    m_save_action = new QAction(tr("&Save ..."), this);
    m_save_action->setShortcuts(QKeySequence::Save);
    m_save_action->setStatusTip(tr("Save game"));
    QObject::connect(m_save_action, SIGNAL(triggered()), this, SLOT(onSaveGame()));

    m_load_action = new QAction(tr("&Load ..."), this);
    m_load_action->setShortcuts(QKeySequence::Open);
    m_load_action->setStatusTip(tr("Load game"));
    QObject::connect(m_load_action, SIGNAL(triggered()), this, SLOT(onLoadGame()));

    m_quit_action = new QAction(tr("E&xit"), this);
    m_quit_action->setShortcuts(QKeySequence::Close);
    m_quit_action->setStatusTip(tr("Load game"));
    QObject::connect(m_quit_action, SIGNAL(triggered()), this, SLOT(close()));

    m_game_menu = menuBar()->addMenu(tr("&Game"));
    m_game_menu->addAction(m_new_action);
    m_game_menu->addAction(m_save_action);
    m_game_menu->addAction(m_load_action);
    m_game_menu->addAction(m_quit_action);
}

void Pexeso::getSettings(int players, int theme, QPoint size)
{
    m_players->setCount(players);
    m_theme->set(theme);
    m_dim->set(size.x(), size.y());
}

void Pexeso::onNewGame()
{
    qDebug() << "New";
}

void Pexeso::onSaveGame()
{
    qDebug() << "Save";
}

void Pexeso::onLoadGame()
{
    qDebug() << "Load";
}
