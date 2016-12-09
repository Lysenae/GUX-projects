#include "board.h"

Board::Board(Dimension *dim, Theme *theme, QWidget *parent) : QWidget(parent)
{
    m_dim    = dim;
    m_theme  = theme;
    m_first  = nullptr;
    m_second = nullptr;
    m_pairs  = m_dim->size()/2;
    setMinimumSize(m_dim->rows()*105, m_dim->cols()*105);
}

Board::~Board()
{
}

void Board::mousePressEvent(QMouseEvent*)
{
    if(m_first != nullptr && m_second != nullptr)
    {
        hideFlippedTiles();
    }
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
        Tile *t = new Tile(v[i], i, m_theme, this);
        m_tiles.append(t);
        m_cols[i / m_dim->cols()]->addWidget(t);
        QObject::connect(t, SIGNAL(clicked()), this, SLOT(onTileClicked()));
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

void Board::hideFlippedTiles()
{
    if(m_first->id() == m_second->id())
    {
        m_first->setCollected();
        m_second->setCollected();
        m_first  = nullptr;
        m_second = nullptr;
        m_pairs--;
        emit endTurn(true);
        if(m_pairs <= 0)
        {
            emit gameOver();
        }
    }
    else
    {
        m_first->toggleFlipped();
        m_second->toggleFlipped();
        m_first  = nullptr;
        m_second = nullptr;
        emit endTurn(false);
    }
}

QVector<QString> Board::toStrings()
{
    QVector<QString> vs;
    QStringList l;
    Tile *t = nullptr;

    l << "first";
    l << QString::number((m_first == nullptr) ? -1 : m_first->order());
    vs.append(l.join(';'));
    l.clear();
    l << "second";
    l << QString::number((m_second == nullptr) ? -1 : m_second->order());
    vs.append(l.join(';'));
    l.clear();

    for(int i=0; i<m_tiles.size(); ++i)
    {
        t = m_tiles[i];
        l << QString::number(t->id());
        l << QString::number(t->isFlipped() ? 1 : 0);
        l << QString::number(t->isCollected() ? 1 : 0);
        vs.append(l.join(';'));
        l.clear();
    }

    return vs;
}

void Board::onTileClicked()
{
    Tile *t = qobject_cast<Tile *>(QObject::sender());


    if(m_first == nullptr)
    {
        if(!t->isFlipped() && !t->isCollected())
        {
            m_first = t;
            t->toggleFlipped();
        }
    }
    else if(m_second == nullptr)
    {
        if(!t->isFlipped() && !t->isCollected())
        {
            m_second = t;
            t->toggleFlipped();
        }
    }
    else
    {
        hideFlippedTiles();
    }
}
