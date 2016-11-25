#ifndef SHAPE_H
#define SHAPE_H

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include "colors.h"

#define ALLOC_STEP 10 // memory allocation stepping

class Shape
{
public:
  static void SetShape(int shape);
  static void SetBorder(int border);
  static void SetLineWidth(int width);
  static void SetFill(bool fill);

  static void InitDrawGC(Widget w);
  static void SetInputGC(Widget w);
  static void SetDrawGC(Widget w);

  static void Draw(Widget w, int x1, int y1, int x2, int y2);
  static void DrawAll(Widget w);

  static void AddLine(int x1, int y1, int x2, int y2);
  static int LinesCount();
  static XSegment* Lines();

  static void ClearAll();
  static void FreeAll();

  static const int POINT         = 0;
  static const int LINE          = 1;
  static const int RECT          = 2;
  static const int ELLIPSE       = 3;
  static const int BORDER_FULL   = 0;
  static const int BORDER_DOTTED = 1;

private:
  static bool m_fill;
  static int m_shape;
  static int m_border;
  static int m_line_width;

  static GC m_input_gc;
  static GC m_draw_gc;
  static Pixel m_fg;
  static Pixel m_bg;

  static XSegment *m_lines;
  static int m_lines_cnt;
  static int m_max_lines;
};

#endif // LINES_H
