#include "shape.h"

bool Shape::m_fill       = false;
int Shape::m_shape       = Shape::POINT;
int Shape::m_border      = Shape::BORDER_FULL;
int Shape::m_line_width  = 1;

XSegment *Shape::m_lines = 0;
int Shape::m_lines_cnt   = 0;
int Shape::m_max_lines   = 0;

void Shape::SetShape(int shape)
{
  m_shape = shape;
}

void Shape::SetBorder(int border)
{
  m_border = border;
}

void Shape::SetLineWidth(int width)
{
  m_line_width = width;
}

void Shape::SetFill(bool fill)
{
  m_fill = fill;
}

// *** LINES ***

void Shape::AddLine(int x1, int y1, int x2, int y2)
{
  if(++m_lines_cnt > m_max_lines)
  {
    m_max_lines += ALLOC_STEP;
    m_lines = (XSegment*) XtRealloc((char*)m_lines,
      (Cardinal)(sizeof(XSegment) * m_max_lines));
  }

  m_lines[m_lines_cnt - 1].x1 = x1;
  m_lines[m_lines_cnt - 1].y1 = y1;
  m_lines[m_lines_cnt - 1].x2 = x2;
  m_lines[m_lines_cnt - 1].y2 = y2;
}

int Shape::LinesCount()
{
  return m_lines_cnt;
}

XSegment* Shape::Lines()
{
  return m_lines;
}


// *** CLEAR ***

void Shape::ClearAll()
{
  m_max_lines = 0;
  m_lines_cnt = 0;
}

void Shape::FreeAll()
{
  ClearAll();
  XtFree((char*)m_lines);
}
