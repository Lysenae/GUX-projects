// GUX Project #1 - Simple graphic editor

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

XSegment *lines    = NULL;  // array of line descriptors
int maxlines       = 0;     // space allocated for max lines
int nlines         = 0;     // current number of lines

GC drawGC          = 0;     // GC used for final drawing
GC inputGC         = 0;     // GC used for drawing current position
int button_pressed = 0;     // input state

int x1, y1, x2, y2;         // input points

/**
 * InputLineEH
 **/
void InputLineEH(Widget w, XtPointer client_data, XEvent *event, Boolean *cont)
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
void DrawLineCB(Widget w, XtPointer client_data, XtPointer call_data)
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
        if (++nlines > maxlines)
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
void ExposeCB(Widget w, XtPointer client_data, XtPointer call_data)
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
void ClearCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Widget wcd = (Widget) client_data;

  nlines = 0;
  XClearWindow(XtDisplay(wcd), XtWindow(wcd));
}

/**
 * "Quit" button callback function
 **/
void QuitCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  exit(0);
}

/**
 * Main
 **/
int main(int argc, char **argv)
{
  XtAppContext app_context;
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

  XtAddCallback(drawArea, XmNinputCallback, DrawLineCB, drawArea);
  XtAddEventHandler(drawArea, ButtonMotionMask, False, InputLineEH, NULL);
  XtAddCallback(drawArea, XmNexposeCallback, ExposeCB, drawArea);

  XtAddCallback(clearBtn, XmNactivateCallback, ClearCB, drawArea);
  XtAddCallback(quitBtn, XmNactivateCallback, QuitCB, 0);

  XtRealizeWidget(topLevel);

  XtAppMainLoop(app_context);

  return 0;
}
