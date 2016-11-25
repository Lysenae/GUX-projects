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
  bool Filled();
  Pixel Foreground();
  Pixel Background();
  XSegment *Line();
  XArc *Ellipse();
  XPoint *Point();

  void SetLine(XSegment *line);
  void SetEllipse(XArc *ellipse);
  void SetPoint(XPoint *Point);

private:
  int       m_type;
  int       m_border;
  int       m_width;
  bool      m_filled;
  Pixel     m_fg;
  Pixel     m_bg;
  XSegment *m_line;
  XArc     *m_ellipse;
  XPoint   *m_point;
};

#endif // SHAPEPROPS_H
