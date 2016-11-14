// GUX Project #1 - Simple graphic editor

#include "mainwindow.h"

// Init static variables
Lines *MainWindow::lines       = new Lines();
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

    if(button_pressed > 1)
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
        lines->add(x1, y1, d->event->xbutton.x, d->event->xbutton.y);
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
  if(lines->count() <= 0)
    return;
  if(!drawGC)
    drawGC = XCreateGC(XtDisplay(w), XtWindow(w), 0, NULL);

  XDrawSegments(XtDisplay(w), XtWindow(w), drawGC, lines->lines(),
    lines->count());
}

/**
 * "Clear" button callback function
 **/
void MainWindow::ClearCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Widget wcd = (Widget) client_data;

  lines->clear();
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
  XtSetLanguageProc(NULL, (XtLanguageProc)NULL, NULL);

  m_top_level = XtVaAppInitialize(
    &m_app_context,
    "Draw",
    NULL, 0,
    &argc, argv,
    NULL,
    XmNx, 300,
    XmNy, 150,
    NULL
  );

  if(!Colors::Init(m_top_level))
  {
    std::cerr << "Failed to initialize colors!" << std::endl;
    exit(1);
  }
  std::cout << "Colors: " << Colors::Count() << std::endl;

  m_main_win = XtVaCreateManagedWidget(
    "mainWin",
    xmMainWindowWidgetClass,
    m_top_level,
    XmNcommandWindowLocation, XmCOMMAND_BELOW_WORKSPACE,
    NULL
  );

  CreateMenu();

  m_frame = XtVaCreateManagedWidget(
    "frame",
    xmFrameWidgetClass,
    m_main_win,
    NULL
  );

  m_draw_area = XtVaCreateManagedWidget(
    "drawingArea",
    xmDrawingAreaWidgetClass,
    m_frame,
    XmNwidth, 500,
    XmNheight, 300,
    XmNminHeight, 150,
    XmNminWidth, 150,
    XmNbackground, Colors::Background(),
    NULL
  );

  m_row_column = XtVaCreateManagedWidget(
    "rowColumn",
    xmRowColumnWidgetClass,
    m_main_win,
    XmNentryAlignment, XmALIGNMENT_CENTER,
    XmNorientation, XmHORIZONTAL,
    XmNpacking, XmPACK_COLUMN,
    NULL
  );

  m_clear_btn = XtVaCreateManagedWidget(
    "Clear",
    xmPushButtonWidgetClass,
    m_row_column,
    NULL
  );

  m_quit_btn = XtVaCreateManagedWidget(
    "Quit",
    xmPushButtonWidgetClass,
    m_row_column,
    NULL
  );

  XmMainWindowSetAreas(m_main_win, NULL, m_row_column, NULL, NULL, m_frame);

  XtAddCallback(m_draw_area, XmNinputCallback, &MainWindow::DrawLineCB, m_draw_area);
  XtAddEventHandler(m_draw_area, ButtonMotionMask, False, InputLineEH, NULL);
  XtAddCallback(m_draw_area, XmNexposeCallback, &MainWindow::ExposeCB, m_draw_area);

  XtAddCallback(m_clear_btn, XmNactivateCallback, &MainWindow::ClearCB,
    m_draw_area);
  XtAddCallback(m_quit_btn, XmNactivateCallback, &MainWindow::QuitCB, 0);

  XtAddCallback(m_menu_clear_btn, XmNactivateCallback, &MainWindow::ClearCB,
    m_draw_area);
  XtAddCallback(m_menu_exit_btn, XmNactivateCallback, &MainWindow::QuitCB, 0);

  XtRealizeWidget(m_top_level);
}

MainWindow::~MainWindow()
{
  delete lines;
}

int MainWindow::run()
{
  XtAppMainLoop(m_app_context);
  return 0;
}

void MainWindow::CreateMenu()
{
  Arg args[4];

  m_menu_bar   = XmCreateMenuBar(m_main_win, (char*)"MenuBar", NULL, 0);
  m_menu       = XmCreatePulldownMenu(m_menu_bar, (char*)"FileMenu", NULL, 0);
  m_menu_w     = XmCreatePulldownMenu(m_menu_bar, (char*)"FilePullDown", NULL, 0);
  m_menu_label = XmStringCreateLocalized((char*)"File");

  XtSetArg(args[0], XmNmnemonic, 'F');
  XtSetArg(args[1], XmNlabelString, m_menu_label);
  XtSetArg(args[2], XmNsubMenuId, m_menu_w);

  m_menu_cascade = XmCreateCascadeButton(m_menu_bar, (char*)"File", args, 3);
  XtManageChild(m_menu_cascade);
  XmStringFree(m_menu_label);

  m_menu_clear_btn =
    XtVaCreateManagedWidget("Clear", xmPushButtonGadgetClass, m_menu_w, NULL);
  m_menu_exit_btn =
    XtVaCreateManagedWidget("Exit", xmPushButtonGadgetClass, m_menu_w, NULL);

  XtManageChild(m_menu_bar);
}
