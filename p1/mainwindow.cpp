// GUX Project #1 - Simple graphic editor

#include "mainwindow.h"

// Init static variables
XSegment *MainWindow::lines    = NULL;
int MainWindow::maxlines       = 0;
int MainWindow::nlines         = 0;
GC MainWindow::drawGC          = 0;
GC MainWindow::inputGC         = 0;
int MainWindow::button_pressed = 0;
int MainWindow::x1             = 0;
int MainWindow::x2             = 0;
int MainWindow::y1             = 0;
int MainWindow::y2             = 0;

/**
 * InputLineEH
 **/
void MainWindow::InputLineEH(Widget w, XtPointer client_data, XEvent *event,
Boolean *cont)
{
  Pixel fg, bg;

  if(button_pressed)
  {
    if(!inputGC)
    {
      inputGC = XCreateGC(XtDisplay(w), XtWindow(w), 0, NULL);
      XSetFunction(XtDisplay(w), inputGC, GXxor);
      XSetPlaneMask(XtDisplay(w), inputGC, ~0);
      XtVaGetValues(w, XmNforeground, &fg, XmNbackground, &bg, NULL);
      XSetForeground(XtDisplay(w), inputGC, fg ^ bg);
    }

    if (button_pressed > 1)
    {
      /* erase previous position */
      XDrawLine(XtDisplay(w), XtWindow(w), inputGC, x1, y1, x2, y2);
    }
    else
    {
      /* remember first MotionNotify */
      button_pressed = 2;
    }

    x2 = event->xmotion.x;
    y2 = event->xmotion.y;

    XDrawLine(XtDisplay(w), XtWindow(w), inputGC, x1, y1, x2, y2);
  }
}

/**
 * "DrawLine" callback function
 **/
void MainWindow::DrawLineCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Arg al[4];
  int ac;
  XGCValues v;
  XmDrawingAreaCallbackStruct *d = (XmDrawingAreaCallbackStruct*) call_data;

  switch (d->event->type)
  {
    case ButtonPress:
    {
      if (d->event->xbutton.button == Button1)
      {
        button_pressed = 1;
        x1 = d->event->xbutton.x;
        y1 = d->event->xbutton.y;
      }
      break;
    }
    case ButtonRelease:
    {
      if(d->event->xbutton.button == Button1)
      {
        if(++nlines > maxlines)
        {
          maxlines += LINES_ALLOC_STEP;
          lines = (XSegment*) XtRealloc((char*)lines,
            (Cardinal)(sizeof(XSegment) * maxlines));
        }

        lines[nlines - 1].x1 = x1;
        lines[nlines - 1].y1 = y1;
        lines[nlines - 1].x2 = d->event->xbutton.x;
        lines[nlines - 1].y2 = d->event->xbutton.y;

        button_pressed = 0;

        if(!drawGC)
        {
          ac = 0;
          XtSetArg(al[ac], XmNforeground, &v.foreground); ac++;
          XtGetValues(w, al, ac);
          drawGC = XCreateGC(XtDisplay(w), XtWindow(w),
          GCForeground, &v);
        }
        XDrawLine(XtDisplay(w), XtWindow(w), drawGC,
          x1, y1, d->event->xbutton.x, d->event->xbutton.y
        );
      }
      break;
    }
  }
}

/**
 * "Expose" callback function
 **/
void MainWindow::ExposeCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  if(nlines <= 0)
    return;
  if(!drawGC)
    drawGC = XCreateGC(XtDisplay(w), XtWindow(w), 0, NULL);
  XDrawSegments(XtDisplay(w), XtWindow(w), drawGC, lines, nlines);
}

/**
 * "Clear" button callback function
 **/
void MainWindow::ClearCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Widget wcd = (Widget) client_data;

  nlines = 0;
  XClearWindow(XtDisplay(wcd), XtWindow(wcd));
}

/**
 * "Quit" button callback function
 **/
void MainWindow::QuitCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  exit(0);
}

/**
 * Main
 **/
MainWindow::MainWindow(int argc, char **argv)
{
  Widget topLevel, mainWin, frame, drawArea, rowColumn, quitBtn, clearBtn;

  XtSetLanguageProc(NULL, (XtLanguageProc)NULL, NULL);

  topLevel = XtVaAppInitialize(
    &app_context,
    "Draw",
    NULL, 0,
    &argc, argv,
    NULL,
    NULL
  );

  mainWin = XtVaCreateManagedWidget(
    "mainWin",
    xmMainWindowWidgetClass,
    topLevel,
    XmNcommandWindowLocation, XmCOMMAND_BELOW_WORKSPACE,
    NULL
  );

  frame = XtVaCreateManagedWidget(
    "frame",
    xmFrameWidgetClass,
    mainWin,
    NULL
  );

  drawArea = XtVaCreateManagedWidget(
    "drawingArea",
    xmDrawingAreaWidgetClass,
    frame,
    XmNwidth, 200,
    XmNheight, 100,
    NULL
  );

  rowColumn = XtVaCreateManagedWidget(
    "rowColumn",
    xmRowColumnWidgetClass,
    mainWin,
    XmNentryAlignment, XmALIGNMENT_CENTER,
    XmNorientation, XmHORIZONTAL,
    XmNpacking, XmPACK_COLUMN,
    NULL
  );

  clearBtn = XtVaCreateManagedWidget("Clear",
    xmPushButtonWidgetClass,
    rowColumn,
    NULL
  );

  quitBtn = XtVaCreateManagedWidget(
    "Quit",
    xmPushButtonWidgetClass,
    rowColumn,
    NULL
  );

  XmMainWindowSetAreas(mainWin, NULL, rowColumn, NULL, NULL, frame);

  XtAddCallback(drawArea, XmNinputCallback, &MainWindow::DrawLineCB, drawArea);
  XtAddEventHandler(drawArea, ButtonMotionMask, False, InputLineEH, NULL);
  XtAddCallback(drawArea, XmNexposeCallback, &MainWindow::ExposeCB, drawArea);

  XtAddCallback(clearBtn, XmNactivateCallback, &MainWindow::ClearCB, drawArea);
  XtAddCallback(quitBtn, XmNactivateCallback, &MainWindow::QuitCB, 0);

  XtRealizeWidget(topLevel);
}

MainWindow::~MainWindow()
{
}

int MainWindow::run()
{
  XtAppMainLoop(app_context);
  return 0;
}
