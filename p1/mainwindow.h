#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/DrawingA.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/PushBG.h>
#include <Xm/CascadeB.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "colors.h"
#include "lines.h"

class MainWindow
{
public:
  MainWindow(int argc, char **argv);
  ~MainWindow();
  int run();

  static void QuitCB(Widget w, XtPointer client_data, XtPointer call_data);
  static void ClearCB(Widget w, XtPointer client_data, XtPointer call_data);
  static void ExposeCB(Widget w, XtPointer client_data, XtPointer call_data);
  static void DrawLineCB(Widget w, XtPointer client_data, XtPointer call_data);
  static void InputLineEH(Widget w, XtPointer client_data, XEvent *event,
    Boolean *cont);

private:
  static Lines *lines;    // array of line descriptors
  static GC drawGC;          // GC used for final drawing
  static GC inputGC;         // GC used for drawing current position
  static int button_pressed; // input state
  static int x1, y1, x2, y2; // input coords

  Widget m_top_level;
  Widget m_main_win;
  Widget m_frame;
  Widget m_draw_area;
  Widget m_row_column;
  Widget m_quit_btn;
  Widget m_clear_btn;

  // Menu
  Widget   m_menu_bar;
  Widget   m_menu;
  Widget   m_menu_w;
  Widget   m_menu_clear_btn;
  Widget   m_menu_exit_btn;
  Widget   m_menu_cascade;
  XmString m_menu_label;

  XtAppContext m_app_context;

  void CreateMenu();
};

#endif // MAINWINDOW_H
