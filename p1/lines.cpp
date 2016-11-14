#include "lines.h"

Lines::Lines()
{
  m_max   = 0;
  m_count = 0;
}

Lines::~Lines()
{
  m_max   = 0;
  m_count = 0;
  XtFree((char*)m_lines);
}

void Lines::add(int x1, int y1, int x2, int y2)
{
  if(++m_count > m_max)
  {
    m_max  += LINES_ALLOC_STEP;
    m_lines = (XSegment*) XtRealloc((char*)m_lines,
      (Cardinal)(sizeof(XSegment) * m_max));
  }

  m_lines[m_count - 1].x1 = x1;
  m_lines[m_count - 1].y1 = y1;
  m_lines[m_count - 1].x2 = x2;
  m_lines[m_count - 1].y2 = y2;
}

int Lines::count()
{
  return m_count;
}

void Lines::clear()
{
  m_count = 0;
}

XSegment* Lines::lines()
{
  return m_lines;
}
