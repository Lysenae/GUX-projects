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

#include <stdio.h>
#include <stdlib.h>

#define LINES_ALLOC_STEP 10 // memory allocation stepping

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
  static XSegment *lines;    // array of line descriptors
  static int maxlines;       // space allocated for max lines
  static int nlines;         // current number of lines
  static GC drawGC;          // GC used for final drawing
  static GC inputGC;         // GC used for drawing current position
  static int button_pressed; // input state

  static int x1, y1, x2, y2;
  XtAppContext app_context;
};

#endif // MAINWINDOW_H
