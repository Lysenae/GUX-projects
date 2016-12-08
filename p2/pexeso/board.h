#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>

#include <QDebug>

#include "dimension.h"
#include "theme.h"
#include "tile.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(Dimension *dim, Theme *theme, QWidget *parent = 0);
    ~Board();
    virtual void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void createBoard();

private:
    Dimension *m_dim;
    Theme     *m_theme;

    QVector<Tile*>  m_tiles;

    QVBoxLayout          *m_rows;
    QVector<QHBoxLayout*> m_cols;

    void shuffleVector(QVector<int> *v);

signals:

public slots:
};

#endif // BOARD_H
