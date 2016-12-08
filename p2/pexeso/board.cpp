#include "board.h"

Board::Board(Dimension *dim, Theme *theme, QWidget *parent) : QWidget(parent)
{
    m_dim   = dim;
    m_theme = theme;
    setMinimumSize(m_dim->rows()*105, m_dim->cols()*105);
}

Board::~Board()
{
}

void Board::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "Board clicked";
}

void Board::createBoard()
{
    m_rows = new QVBoxLayout();
    m_rows->setSpacing(5);

    QVector<int> v;
    for(int i=1; i<=m_dim->size()/2; ++i)
    {
        v.append(i);
        v.append(i);
    }
    shuffleVector(&v);
    shuffleVector(&v);
    shuffleVector(&v);
    shuffleVector(&v);
    shuffleVector(&v);

    for(int i=0; i<m_dim->rows(); ++i)
    {
        QHBoxLayout *tmp = new QHBoxLayout();
        m_rows->addLayout(tmp);
        m_cols.append(tmp);
    }

    for(int i=0; i<m_dim->size(); ++i)
    {
        Tile *t = new Tile(v[i], m_theme, this);
        m_tiles.append(t);
        m_cols[i / m_dim->cols()]->addWidget(t);
    }

    setLayout(m_rows);
}

void Board::shuffleVector(QVector<int> *v)
{
    int i = v->size();
    int j, t;
    while(i > 1)
    {
        i = i - 1;
        qsrand(QTime::currentTime().msec());
        j = qrand() % i;
        t = v->at(i);
        v->replace(i, v->at(j));
        v->replace(j, t);
    }
}
