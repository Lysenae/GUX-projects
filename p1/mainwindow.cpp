// GUX Project #1 - Simple graphic editor

#include "mainwindow.h"

// Init static variables
Lines *MainWindow::m_lines         = new Lines();
GC MainWindow::m_draw_gc           = 0;
GC MainWindow::m_input_gc          = 0;
int MainWindow::m_button_pressed   = 0;
int MainWindow::x1                 = 0;
int MainWindow::x2                 = 0;
int MainWindow::y1                 = 0;
int MainWindow::y2                 = 0;
Widget MainWindow::m_shape_point   = 0;
Widget MainWindow::m_shape_line    = 0;
Widget MainWindow::m_shape_rect    = 0;
Widget MainWindow::m_shape_ellipse = 0;
Widget MainWindow::m_border_full   = 0;
Widget MainWindow::m_border_dotted = 0;
Widget MainWindow::m_fill_btn      = 0;
int MainWindow::m_shape            = MainWindow::SHAPE_POINT;
int MainWindow::m_border           = MainWindow::BORDER_FULL;
bool MainWindow::m_fill            = false;

/**
 * InputLineEH
 **/
void MainWindow::InputLineEH(Widget w, XtPointer client_data, XEvent *event,
Boolean *cont)
{
  Pixel fg, bg;

  if(m_button_pressed)
  {
    if(!m_input_gc)
    {
      m_input_gc = XCreateGC(XtDisplay(w), XtWindow(w), 0, NULL);
      XSetFunction(XtDisplay(w), m_input_gc, GXxor);
      XSetPlaneMask(XtDisplay(w), m_input_gc, ~0);
      XtVaGetValues(w, XmNforeground, &fg, XmNbackground, &bg, NULL);
      XSetForeground(XtDisplay(w), m_input_gc, fg ^ bg);
    }

    if(m_button_pressed > 1)
    {
      /* erase previous position */
      XDrawLine(XtDisplay(w), XtWindow(w), m_input_gc, x1, y1, x2, y2);
    }
    else
    {
      /* remember first MotionNotify */
      m_button_pressed = 2;
    }

    x2 = event->xmotion.x;
    y2 = event->xmotion.y;

    XDrawLine(XtDisplay(w), XtWindow(w), m_input_gc, x1, y1, x2, y2);
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
        m_button_pressed = 1;
        x1 = d->event->xbutton.x;
        y1 = d->event->xbutton.y;
      }
      break;
    }
    case ButtonRelease:
    {
      if(d->event->xbutton.button == Button1)
      {
        m_lines->add(x1, y1, d->event->xbutton.x, d->event->xbutton.y);
        m_button_pressed = 0;

        if(!m_draw_gc)
        {
          ac = 0;
          XtSetArg(al[ac], XmNforeground, &v.foreground); ac++;
          XtGetValues(w, al, ac);
          m_draw_gc = XCreateGC(XtDisplay(w), XtWindow(w),
          GCForeground, &v);
        }
        XDrawLine(XtDisplay(w), XtWindow(w), m_draw_gc,
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
  if(m_lines->count() <= 0)
    return;
  if(!m_draw_gc)
    m_draw_gc = XCreateGC(XtDisplay(w), XtWindow(w), 0, NULL);

  XDrawSegments(XtDisplay(w), XtWindow(w), m_draw_gc, m_lines->lines(),
    m_lines->count());
}

/**
 * "Clear" button callback function
 **/
void MainWindow::ClearCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Widget wcd = (Widget) client_data;

  m_lines->clear();
  XClearWindow(XtDisplay(wcd), XtWindow(wcd));
}

/**
 * "Quit" button callback function
 **/
void MainWindow::QuitCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  exit(0);
}

void MainWindow::OnShapeToggled(Widget w, XtPointer client_data,
XtPointer call_data)
{
  if(w == m_shape_point)
  {
    XmToggleButtonSetState(m_shape_point, True, False);
    XmToggleButtonSetState(m_shape_line, False, False);
    XmToggleButtonSetState(m_shape_rect, False, False);
    XmToggleButtonSetState(m_shape_ellipse, False, False);
    m_shape = SHAPE_POINT;
  }
  else if(w == m_shape_line)
  {
    XmToggleButtonSetState(m_shape_point, False, False);
    XmToggleButtonSetState(m_shape_line, True, False);
    XmToggleButtonSetState(m_shape_rect, False, False);
    XmToggleButtonSetState(m_shape_ellipse, False, False);
    m_shape = SHAPE_LINE;
  }
  else if(w == m_shape_rect)
  {
    XmToggleButtonSetState(m_shape_point, False, False);
    XmToggleButtonSetState(m_shape_line, False, False);
    XmToggleButtonSetState(m_shape_rect, True, False);
    XmToggleButtonSetState(m_shape_ellipse, False, False);
    m_shape = SHAPE_RECT;
  }
  else if(w == m_shape_ellipse)
  {
    XmToggleButtonSetState(m_shape_point, False, False);
    XmToggleButtonSetState(m_shape_line, False, False);
    XmToggleButtonSetState(m_shape_rect, False, False);
    XmToggleButtonSetState(m_shape_ellipse, True, False);
    m_shape = SHAPE_ELLIPSE;
  }
  else
  {
    std::cerr << "Invalid shape button ID" << std::endl;
  }

  std::cout << "Shape ID: " << m_shape << std::endl;
}

void MainWindow::OnBorderToggled(Widget w, XtPointer client_data,
XtPointer call_data)
{
  if(w == m_border_full)
  {
    XmToggleButtonSetState(m_border_full, True, False);
    XmToggleButtonSetState(m_border_dotted, False, False);
    m_border = BORDER_FULL;
  }
  else if(w == m_border_dotted)
  {
    XmToggleButtonSetState(m_border_full, False, False);
    XmToggleButtonSetState(m_border_dotted, True, False);
    m_border = BORDER_DOTTED;
  }
  else
  {
    std::cerr << "Invalid border type ID" << std::endl;
  }

  std::cout << "Border: " << m_border << std::endl;
}

void MainWindow::OnFillToggled(Widget w, XtPointer client_data,
XtPointer call_data)
{
  if(XmToggleButtonGetState(w) == True)
  {
    m_fill = true;
  }
  else
  {
    m_fill = false;
  }

  std::cout << "Fill: " << m_fill << std::endl;
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

  m_tools = XtVaCreateManagedWidget(
    "tools",
    xmRowColumnWidgetClass,
    m_main_win,
    XmNentryAlignment, XmALIGNMENT_BEGINNING,
    XmNorientation, XmVERTICAL,
    XmNpacking, XmPACK_TIGHT,
    NULL
  );

  m_tools_shapes = XtVaCreateManagedWidget(
    "toolsShapes",
    xmRowColumnWidgetClass,
    m_tools,
    XmNentryAlignment, XmALIGNMENT_CENTER,
    XmNorientation, XmHORIZONTAL,
    XmNpacking, XmPACK_COLUMN,
    NULL
  );

  m_tools_border_fill = XtVaCreateManagedWidget(
    "toolsBorderFill",
    xmRowColumnWidgetClass,
    m_tools,
    XmNentryAlignment, XmALIGNMENT_CENTER,
    XmNorientation, XmHORIZONTAL,
    XmNpacking, XmPACK_COLUMN,
    NULL
  );

  CreateTools();

  XmMainWindowSetAreas(m_main_win, NULL, m_tools, NULL, NULL, m_frame);

  XtAddCallback(m_draw_area, XmNinputCallback, &MainWindow::DrawLineCB, m_draw_area);
  XtAddEventHandler(m_draw_area, ButtonMotionMask, False, InputLineEH, NULL);
  XtAddCallback(m_draw_area, XmNexposeCallback, &MainWindow::ExposeCB, m_draw_area);

  XtAddCallback(m_menu_clear_btn, XmNactivateCallback, &MainWindow::ClearCB,
    m_draw_area);
  XtAddCallback(m_menu_exit_btn, XmNactivateCallback, &MainWindow::QuitCB, 0);

  XtRealizeWidget(m_top_level);
}

MainWindow::~MainWindow()
{
  delete m_lines;
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

  m_menu_accel = XmStringCreateLocalized((char*)"Ctrl+C");
  XtSetArg(args[0], XmNaccelerator, "Ctrl<Key>C");
  XtSetArg(args[1], XmNacceleratorText, m_menu_accel);
  XtSetArg(args[2], XmNmnemonic, 'C');
  m_menu_clear_btn = XmCreatePushButtonGadget(m_menu_w, (char*)"Clear", args, 3);
  XtManageChild(m_menu_clear_btn);

  m_menu_accel = XmStringCreateLocalized((char*)"Ctrl+X");
  XtSetArg(args[0], XmNaccelerator, "Ctrl<Key>X");
  XtSetArg(args[1], XmNacceleratorText, m_menu_accel);
  XtSetArg(args[2], XmNmnemonic, 'x');
  m_menu_exit_btn = XmCreatePushButtonGadget(m_menu_w, (char*)"Exit", args, 3);
  XtManageChild(m_menu_exit_btn);

  XmStringFree(m_menu_accel);
  XtManageChild(m_menu_bar);
}

void MainWindow::CreateTools()
{
  m_shape_point = XtVaCreateManagedWidget(
    "Point",
    xmToggleButtonWidgetClass,
    m_tools_shapes,
    NULL
  );
  XtAddCallback(m_shape_point, XmNvalueChangedCallback, OnShapeToggled, NULL);
  XmToggleButtonSetState(m_shape_point, True, False);

  m_shape_line = XtVaCreateManagedWidget(
    "Line",
    xmToggleButtonWidgetClass,
    m_tools_shapes,
    NULL
  );
  XtAddCallback(m_shape_line, XmNvalueChangedCallback, OnShapeToggled, NULL);

  m_shape_rect = XtVaCreateManagedWidget(
    "Rectangle",
    xmToggleButtonWidgetClass,
    m_tools_shapes,
    NULL
  );
  XtAddCallback(m_shape_rect, XmNvalueChangedCallback, OnShapeToggled, NULL);

  m_shape_ellipse = XtVaCreateManagedWidget(
    "Ellipse",
    xmToggleButtonWidgetClass,
    m_tools_shapes,
    NULL
  );
  XtAddCallback(m_shape_ellipse, XmNvalueChangedCallback, OnShapeToggled, NULL);

  m_border_full = XtVaCreateManagedWidget(
    "Full line",
    xmToggleButtonWidgetClass,
    m_tools_border_fill,
    NULL
  );
  XtAddCallback(m_border_full, XmNvalueChangedCallback, OnBorderToggled, NULL);
  XmToggleButtonSetState(m_border_full, True, False);

  m_border_dotted = XtVaCreateManagedWidget(
    "Dotted line",
    xmToggleButtonWidgetClass,
    m_tools_border_fill,
    NULL
  );
  XtAddCallback(m_border_dotted, XmNvalueChangedCallback, OnBorderToggled, NULL);

  m_fill_btn = XtVaCreateManagedWidget(
    "Fill rectangle/ellipse",
    xmToggleButtonWidgetClass,
    m_tools_border_fill,
    NULL
  );
  XtAddCallback(m_fill_btn, XmNvalueChangedCallback, OnFillToggled, NULL);
}
