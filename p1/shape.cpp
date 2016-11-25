#include "shape.h"

bool Shape::m_fill       = false;
int Shape::m_shape       = Shape::POINT;
int Shape::m_border      = Shape::BORDER_FULL;
int Shape::m_line_width  = 1;

GC Shape::m_input_gc     = 0;
GC Shape::m_draw_gc      = 0;
Pixel Shape::m_fg        = 0;
Pixel Shape::m_bg        = 0;

std::vector<ShapeProperties> Shape::m_shapes;

int Shape::m_lines_cnt   = 0;
int Shape::m_max_lines   = 0;

ShapeProperties::ShapeProperties(int type, int border, int width, bool filled,
Pixel fg, Pixel bg)
{
  m_type = type;
  m_border = border;
  m_width = width;
  m_filled = filled;
  m_fg = fg;
  m_bg = bg;
}

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
  if(m_shape == Shape::LINE)
  {
    XDrawLine(XtDisplay(w), XtWindow(w), m_input_gc, x1, y1, x2, y2);
  }
}

void Shape::DrawAll(Widget w)
{
  for(unsigned int i=0; i<m_shapes.size(); ++i)
  {
    if(m_shapes[i].m_type == Shape::LINE)
    {
      XDrawSegments(XtDisplay(w), XtWindow(w), m_draw_gc, m_shapes[i].m_line, 1);
    }
  }
}

// *** LINES ***

void Shape::Add(int x1, int y1, int x2, int y2)
{
  ShapeProperties s = ShapeProperties(
    m_shape, m_border, m_line_width, m_fill,
    Colors::Foreground(), Colors::Background()
  );

  if(m_shape == Shape::LINE)
  {
    ++m_lines_cnt;
    s.m_line = (XSegment*) XtMalloc((Cardinal)sizeof(XSegment));
    s.m_line->x1 = x1;
    s.m_line->y1 = y1;
    s.m_line->x2 = x2;
    s.m_line->y2 = y2;
  }
  m_shapes.push_back(s);
}

int Shape::LinesCount()
{
  return m_lines_cnt;
}

std::vector<ShapeProperties> Shape::All()
{
  return m_shapes;
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
  //XtFree((char*)m_lines);
}
