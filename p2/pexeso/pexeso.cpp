#include "pexeso.h"

Pexeso::Pexeso(QWidget *parent) : QMainWindow(parent)
{
    m_ngd = new NewGameDialog();

    m_dim     = new Dimension(0, 0);
    m_players = new Players();
    m_theme   = new Theme();

    QObject::connect(m_ngd, SIGNAL(passSettings(int, int, QPoint)),
        this, SLOT(getSettings(int, int, QPoint)));
}

Pexeso::~Pexeso()
{
}

void Pexeso::getSettings(int players, int theme, QPoint size)
{
    m_players->setCount(players);
    m_theme->set(theme);
    m_dim->set(size.x(), size.y());
}
