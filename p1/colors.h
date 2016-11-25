// File:        colors.h
// Author:      Daniel Klimaj (xklima22)
// Description: Initializes and sets colors.

#ifndef COLORS_H
#define COLORS_H

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

class Colors
{
public:
  static bool Init(Widget shell);
  static Pixel Background();
  static Pixel Foreground();
  static void SetBackground(unsigned int i);
  static void SetForeground(unsigned int i);
  static int Count();
  static std::vector<std::string> Names();
  static std::string Name(unsigned int i);

private:
  static std::vector<std::string> m_color_names;
  static std::vector<Pixel> m_colors;
  static Pixel m_background;
  static Pixel m_foreground;

  static std::vector<std::string> InitNames();
};

#endif // COLORS_H
