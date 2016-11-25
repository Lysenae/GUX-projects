#include "shape.h"

bool Shape::m_fill       = false;
int Shape::m_shape       = Shape::POINT;
int Shape::m_border      = Shape::BORDER_FULL;
int Shape::m_line_width  = 1;

GC Shape::m_input_gc     = 0;
GC Shape::m_draw_gc      = 0;
Pixel Shape::m_fg        = 0;
Pixel Shape::m_bg        = 0;

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

void Shape::InitDrawGC(Widget w)
{
  if(!m_draw_gc)
  {
    m_draw_gc = XCreateGC(XtDisplay(w), XtWindow(w), 0, NULL);
  }
}

void Shape::SetInputGC(Widget w)
{
  if(!m_input_gc)
  {
    m_input_gc = XCreateGC(XtDisplay(w), XtWindow(w), 0, NULL);
    XSetFunction(XtDisplay(w), m_input_gc, GXxor);
    XSetPlaneMask(XtDisplay(w), m_input_gc, ~0);
    XtVaGetValues(w, XmNforeground, &m_fg, XmNbackground, &m_bg, NULL);
    XSetForeground(XtDisplay(w), m_input_gc, m_fg ^ m_bg);
  }
}

void Shape::SetDrawGC(Widget w)
{
  Arg al[4];
  int ac;
  XGCValues v;

  if(!m_draw_gc)
  {
    ac = 0;
    XtSetArg(al[ac], XmNforeground, &v.foreground); ac++;
    XtGetValues(w, al, ac);
    m_draw_gc = XCreateGC(XtDisplay(w), XtWindow(w), GCForeground, &v);
  }
}

void Shape::Draw(Widget w, int x1, int y1, int x2, int y2)
{
  XDrawLine(XtDisplay(w), XtWindow(w), m_input_gc, x1, y1, x2, y2);
}

void Shape::DrawAll(Widget w)
{
  XDrawSegments(XtDisplay(w), XtWindow(w), m_draw_gc, Lines(), LinesCount());
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
