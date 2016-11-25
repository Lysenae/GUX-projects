#ifndef SHAPEPROPS_H
#define SHAPEPROPS_H

#include <Xm/Xm.h>

class ShapeProperties
{
public:
  ShapeProperties(int type, int border, int width, bool filled, Pixel fg,
    Pixel bg);
  int Type();
  int Border();
  int LineWidth();
  Pixel Foreground();
  Pixel Background();
  XSegment *Line();
  XArc *Ellipse();

  void SetLine(XSegment *line);
  void SetEllipse(XArc *ellipse);

private:
  int       m_type;
  int       m_border;
  int       m_width;
  bool      m_filled;
  Pixel     m_fg;
  Pixel     m_bg;
  XSegment *m_line;
  XArc     *m_ellipse;
};

#endif // SHAPEPROPS_H
