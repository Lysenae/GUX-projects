#ifndef LINES_H
#define LINES_H

#include <X11/Intrinsic.h>

#define LINES_ALLOC_STEP 10 // memory allocation stepping

class Lines
{
public:
  Lines();
  ~Lines();
  void add(int x1, int y1, int x2, int y2);
  int count();
  void clear();
  XSegment* lines();

private:
  XSegment *m_lines;
  int m_count;
  int m_max;
};

#endif // LINES_H
