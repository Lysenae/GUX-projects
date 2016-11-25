#include "shapeproperties.h"

ShapeProperties::ShapeProperties(int type, int border, int width, bool filled,
Pixel fg, Pixel bg)
{
  m_type    = type;
  m_border  = border;
  m_width   = width;
  m_filled  = filled;
  m_fg      = fg;
  m_bg      = bg;
  m_line    = NULL;
  m_ellipse = NULL;
  m_point   = NULL;
}

int ShapeProperties::Type()
{
  return m_type;
}

int ShapeProperties::Border()
{
  return m_border;
}

int ShapeProperties::LineWidth()
{
  return m_width;
}

bool ShapeProperties::Filled()
{
  return m_filled;
}

Pixel ShapeProperties::Foreground()
{
  return m_fg;
}

Pixel ShapeProperties::Background()
{
  return m_bg;
}

XSegment *ShapeProperties::Line()
{
  return m_line;
}

XArc *ShapeProperties::Ellipse()
{
  return m_ellipse;
}

XPoint *ShapeProperties::Point()
{
  return m_point;
}

void ShapeProperties::SetLine(XSegment *line)
{
  m_line = line;
}

void ShapeProperties::SetEllipse(XArc *ellipse)
{
  m_ellipse = ellipse;
}

void ShapeProperties::SetPoint(XPoint *point)
{
  m_point = point;
}
