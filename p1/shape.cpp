#include "shape.h"

bool Shape::m_fill       = false;
int Shape::m_shape       = Shape::POINT;
int Shape::m_border      = Shape::BORDER_FULL;
int Shape::m_line_width  = 1;

GC Shape::m_input_gc     = 0;
GC Shape::m_draw_gc      = 0;
Pixel Shape::m_fg        = 0;
Pixel Shape::m_bg        = 0;

int Shape::m_lines_cnt   = 0;

std::vector<ShapeProperties*> Shape::m_shapes;

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

int Shape::Border(int border)
{
  return border == Shape::BORDER_FULL ? LineSolid : LineDoubleDash;
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
  if(m_shape == Shape::LINE)
  {
    XDrawLine(XtDisplay(w), XtWindow(w), m_input_gc, x1, y1, x2, y2);
  }
  else if(m_shape == Shape::ELLIPSE)
  {
    int width  = Width(x1, x2);
    int height = Height(y1, y2);
    if(m_fill)
    {
      XFillArc(XtDisplay(w), XtWindow(w), m_input_gc, x1, y1, width, height,
        Shape::ANGLE1, Shape::ANGLE2);
    }
    else
    {
      XDrawArc(XtDisplay(w), XtWindow(w), m_input_gc, x1, y1, width, height,
        Shape::ANGLE1, Shape::ANGLE2);
    }
  }
}

void Shape::DrawAll(Widget w)
{
  for(unsigned int i=0; i<m_shapes.size(); ++i)
  {
    XGCValues gcv;
    gcv.line_style     = Border(m_shapes[i]->Border());
    gcv.line_width     = m_shapes[i]->LineWidth();
    gcv.foreground     = m_shapes[i]->Foreground();
    gcv.background     = m_shapes[i]->Background();
    unsigned long mask = GCForeground | GCBackground | GCLineWidth | GCLineStyle;
    XChangeGC(XtDisplay(w), m_draw_gc, mask, &gcv);
    
    if(m_shapes[i]->Type() == Shape::LINE)
    {
      XDrawSegments(XtDisplay(w), XtWindow(w), m_draw_gc, m_shapes[i]->Line(), 1);
    }
  }
}

void Shape::SetInputStyle(Widget w)
{
  XGCValues gcv;
  gcv.line_style     = Border(m_border);
  gcv.line_width     = m_line_width;
  gcv.foreground     = Colors::Foreground() ^ m_bg;
  gcv.background     = Colors::Background() ^ m_bg;
  unsigned long mask = GCForeground | GCBackground | GCLineWidth | GCLineStyle;
  XChangeGC(XtDisplay(w), m_input_gc, mask, &gcv);
}

void Shape::SetDrawStyle(Widget w)
{
  XGCValues gcv;
  gcv.line_style     = Border(m_border);
  gcv.line_width     = m_line_width;
  gcv.foreground     = Colors::Foreground();
  gcv.background     = Colors::Background();
  unsigned long mask = GCForeground | GCBackground | GCLineWidth | GCLineStyle;
  XChangeGC(XtDisplay(w), m_draw_gc, mask, &gcv);
}

// *** LINES ***

void Shape::Add(int x1, int y1, int x2, int y2)
{
  ShapeProperties *s = new ShapeProperties(
    m_shape, m_border, m_line_width, m_fill,
    Colors::Foreground(), Colors::Background()
  );

  if(m_shape == Shape::LINE)
  {
    ++m_lines_cnt;
    XSegment *line = (XSegment*) XtMalloc((Cardinal)sizeof(XSegment));
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    s->SetLine(line);
  }
  m_shapes.push_back(s);
}

int Shape::LinesCount()
{
  return m_lines_cnt;
}

std::vector<ShapeProperties*> Shape::All()
{
  return m_shapes;
}


// *** CLEAR ***

void Shape::ClearAll()
{
  m_lines_cnt = 0;
  for(unsigned int i=0; i<m_shapes.size(); i++)
  {
    if(m_shapes[i]->Type() == Shape::LINE)
    {
      XtFree((char*)(m_shapes[i]->Line()));
    }
  }
  m_shapes.clear();
}

int Shape::Width(int x1, int x2)
{
  return x1 >= x2 ? x1 - x2 : x2 - x1;
}

int Shape::Height(int y1, int y2)
{
  return y1 >= y2 ? y1 - y2 : y2 - y1;
}
