#include "dimension.h"

Dimension::Dimension(int rows, int cols)
{
    set(rows, cols);
}

int Dimension::size()
{
    return m_cols * m_rows;
}

int Dimension::rows()
{
    return m_rows;
}

int Dimension::cols()
{
    return m_cols;
}

void Dimension::set(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
}

QString Dimension::toString()
{
    return QString::number(m_rows) + "x" + QString::number(m_cols);
}
