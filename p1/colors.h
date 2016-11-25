// File:        colors.h
// Author:      Daniel Klimaj (xklima22)
// Description: Initializes and sets colors.

#ifndef COLORS_H
#define COLORS_H

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define COLORS 6

class Colors
{
public:
  static bool Init(Widget shell);
  static Pixel Background();
  static Pixel Foreground();
  static void SetBackground(unsigned int i);
  static void SetForeground(unsigned int i);
  static int Count();
  static char **Names();
  static char *Name(unsigned int i);

private:
  static char *m_color_names[COLORS];
  static Pixel *m_colors;
  static Pixel m_background;
  static Pixel m_foreground;

  static char **InitNames();
};

#endif // COLORS_H
