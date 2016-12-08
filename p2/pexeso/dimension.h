#ifndef DIMENSION_H
#define DIMENSION_H


class Dimension
{
public:
    Dimension(int rows, int cols);
    int size();
    int rows();
    int cols();
    void set(int rows, int cols);

private:
    int m_cols;
    int m_rows;
};

#endif // DIMENSION_H
