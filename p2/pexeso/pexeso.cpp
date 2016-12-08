#include "pexeso.h"

Pexeso::Pexeso(QWidget *parent) : QMainWindow(parent)
{
    m_ngd = new NewGameDialog();

    m_dim     = new Dimension(0, 0);
    m_players = new Players();
    m_theme   = new Theme();
    m_window  = new QWidget();

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

void Pexeso::createLayout()
{
    m_main_lt = new QHBoxLayout();
    m_info_lt = new QVBoxLayout();
    m_board   = new QScrollArea();

    m_players_ld = new QLabel(QString(tr("Players:")), m_window);
    m_players_lv = new QLabel(QString::number(m_players->count()), m_window);
    m_theme_ld   = new QLabel(QString(tr("Theme:")), m_window);
    m_theme_lv   = new QLabel(m_theme->toString(), m_window);
    m_size_ld    = new QLabel(QString(tr("Size:")), m_window);
    m_size_lv    = new QLabel(m_dim->toString(), m_window);
    m_cplayer_ld = new QLabel(QString(tr("Player's turn:")), m_window);
    m_cplayer_lv = new QLabel(QString::number(m_players->current()), m_window);

    m_info_w_main  = new QWidget(m_window);
    m_info_w_main->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    m_info_lt_main = new QHBoxLayout();
    m_info_lt_desc = new QVBoxLayout();
    m_info_lt_val  = new QVBoxLayout();

    m_info_lt_desc->addWidget(m_players_ld);
    m_info_lt_desc->addWidget(m_size_ld);
    m_info_lt_desc->addWidget(m_theme_ld);
    m_info_lt_desc->addWidget(m_cplayer_ld);

    m_info_lt_val->addWidget(m_players_lv);
    m_info_lt_val->addWidget(m_size_lv);
    m_info_lt_val->addWidget(m_theme_lv);
    m_info_lt_val->addWidget(m_cplayer_lv);

    m_info_lt_main->addLayout(m_info_lt_desc);
    m_info_lt_main->addLayout(m_info_lt_val);
    m_info_w_main->setLayout(m_info_lt_main);

    m_info_lt->addWidget(m_info_w_main);
    m_info_lt->addSpacing(5);

    m_scores_w = new QWidget();
    m_scores_w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    m_scores_lt = new QVBoxLayout();
    m_scores_lt->setAlignment(Qt::AlignLeft);

    QString temp;
    for(int i=0; i<m_players->count(); ++i)
    {
        temp = QString("Player " + QString::number(i+1) + ": " +
            QString::number(m_players->getScore(i+1)));
        m_scores.append(new QLabel(temp, m_window));
    }

    for(int i=0; i<m_scores.size(); ++i)
    {
        m_scores_lt->addWidget(m_scores[i], 0, Qt::AlignTop);
    }

    m_scores_w->setLayout(m_scores_lt);
    m_info_lt->addWidget(m_scores_w);

    m_info_lt->addStretch();

    m_info_w = new QWidget();
    m_info_w->setGeometry(m_info_w->geometry().x(), m_info_w->geometry().y(),
        250, m_info_w->geometry().height());
    m_info_w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_info_w->setLayout(m_info_lt);

    m_board->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_board->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_board->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Hlavny layout
    m_main_lt->addWidget(m_info_w);
    m_main_lt->addWidget(m_board);

    m_window->setLayout(m_main_lt);

    setCentralWidget(m_window);
}

void Pexeso::clearBoard()
{
    if(m_window != nullptr)
    {
        delete m_window;
        m_window = new QWidget();
        setCentralWidget(nullptr);
    }

    m_scores.clear();
}

void Pexeso::createNewGame()
{
    createLayout();
}

void Pexeso::getSettings(int players, int theme, QPoint size)
{
    m_players->setCount(players);
    m_theme->set(theme);
    m_dim->set(size.x(), size.y());
}

void Pexeso::onNewGame()
{
    if(m_ngd->exec() == QDialog::Accepted)
    {
        clearBoard();
        createNewGame();
    }
}

void Pexeso::onSaveGame()
{
    qDebug() << "Save";
}

void Pexeso::onLoadGame()
{
    qDebug() << "Load";
}
