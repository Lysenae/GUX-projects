#include "tile.h"

Tile::Tile(int id, Theme *theme, QPoint position, QWidget *parent)
 : QWidget(parent)
{
    m_id        = id;
    m_flipped   = false;
    m_collected = false;
    m_theme     = theme;
    m_position  = position;

    m_pm    = new QPixmap(m_theme->loadImage(BACK));
    m_scene = new QGraphicsScene();
    m_gi    = new QGraphicsPixmapItem(*m_pm);

    m_view = new QGraphicsView(m_scene);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->fitInView(0, 0, m_pm->width()*10, m_pm->height(), Qt::KeepAspectRatio);

    m_layout = new QHBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_view);
    m_layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(m_layout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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

    m_pm = new QPixmap(m_theme->loadImage(id));
    if(m_gi) delete m_gi;
    m_scene->clear();
    m_gi = new QGraphicsPixmapItem(*m_pm);
    m_scene->addItem(m_gi);
    m_view->update();
}
