#include "tile.h"

Tile::Tile(int id, Theme *theme, QWidget *parent)
 : QWidget(parent)
{
    m_id        = id;
    m_flipped   = true;
    m_collected = false;
    m_theme     = theme;

    QPixmap p = QPixmap(m_theme->imageName(id)).scaled(100, 100);
    m_pm    = new QPixmap(p);
    m_scene = new QGraphicsScene();
    m_gi    = new QGraphicsPixmapItem(*m_pm);

    m_scene->addItem(m_gi);

    m_view = new QGraphicsView(m_scene);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_layout = new QHBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_view);
    m_layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(m_layout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void Tile::mousePressEvent(QMouseEvent *e)
{
    if(!m_flipped && !m_collected)
    {
        m_flipped = true;
    }
    else if(m_flipped && !m_collected)
    {
        m_collected = true;
    }
    else
    {
        m_flipped   = false;
        m_collected = false;
    }

    changePixmap();
}

void Tile::changePixmap()
{
    if(m_pm) delete m_pm;

    int id;
    if(m_flipped && !m_collected)
        id = m_id;
    else if(!m_flipped && !m_collected)
        id = BACK;
    else
        id = BLANK;

    QPixmap p = QPixmap(m_theme->imageName(id)).scaled(100, 100);
    m_pm = new QPixmap(p);
    if(m_gi) delete m_gi;
    m_scene->clear();
    m_gi = new QGraphicsPixmapItem(*m_pm);
    m_scene->addItem(m_gi);
    m_view->update();
}
