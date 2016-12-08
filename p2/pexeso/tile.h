#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QHBoxLayout>
#include <QMouseEvent>

#include "theme.h"

class Tile : public QWidget
{
    Q_OBJECT

public:
    explicit Tile(int id, Theme *theme, QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

private:
    const int BACK  = 0;
    const int BLANK = -1;

    int     m_id;
    bool    m_flipped;
    bool    m_collected;
    Theme  *m_theme;

    QPixmap             *m_pm;
    QGraphicsScene      *m_scene;
    QGraphicsView       *m_view;
    QGraphicsPixmapItem *m_gi;

    QHBoxLayout *m_layout;

    void changePixmap();

signals:

public slots:
};

#endif // TILE_H
