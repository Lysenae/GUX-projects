#include "colors.h"

// Initialize static variables/structures
std::vector<std::string> Colors::m_color_names = InitColorNames();
std::vector<Pixel> Colors::m_colors;
Pixel Colors::m_background;
Pixel Colors::m_foreground;

void Colors::Init(Widget shell)
{
  XColor col_screen, col_exact;
  XWindowAttributes win_attrs;

  Display  *display = XtDisplay(shell);
  Screen   *screen  = XtScreen(shell);
  Colormap  colmap  = DefaultColormapOfScreen(screen);

  XGetWindowAttributes(display, RootWindowOfScreen(screen), &win_attrs);

  for(unsigned int i=0; i<m_color_names.size(); i++)
  {
    if(XAllocNamedColor(display, colmap, m_color_names[i].c_str(),
    &col_screen, &col_exact) == 0)
    {
      std::cerr << "Failed to initialize color '" << m_color_names[i] <<
        "'" << std::endl;
      return;
    }
    m_colors.push_back(col_screen.pixel);
  }
  m_background = m_colors[0];
  m_foreground = m_colors[1];
}

Pixel Colors::background()
{
  return m_background;
}

Pixel Colors::foreground()
{
  return m_foreground;
}

int Colors::count()
{
  return m_colors.size();
}

std::vector<std::string> Colors::InitColorNames()
{
  std::vector<std::string> v;
  v.push_back("white");
  v.push_back("black");
  v.push_back("gold");
  v.push_back("olive");
  v.push_back("maroon");
  v.push_back("indigo");
  return v;
}