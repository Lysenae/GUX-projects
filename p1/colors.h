#ifndef COLORS_H
#define COLORS_h

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include <vector>
#include <iostream>
#include <string>

class Colors
{
public:
  static bool Init(Widget shell);
  static Pixel background();
  static Pixel foreground();
  static int count();

private:
  static std::vector<std::string> m_color_names;
  static std::vector<Pixel> m_colors;
  static Pixel m_background;
  static Pixel m_foreground;

  static std::vector<std::string> InitColorNames();
};

#endif // COLORS_H
