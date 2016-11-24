#ifndef QUITDIALOG_H
#define QUITDIALOG_H

#include <Xm/Xm.h>
#include <Xm/MessageB.h>

class QuitDialog
{
public:
  QuitDialog(Widget parent);
  ~QuitDialog();
  void Show();
  bool Result();

private:
  static Widget m_quit_dialog;
  static bool   m_rslt;
  static bool   m_up;

  XmString m_msg;
  XmString m_quit;
  XmString m_cancel;

  static void OnQuitClicked(Widget w, XtPointer client_data,
    XtPointer call_data);
  static void OnCancelClicked(Widget w, XtPointer client_data,
    XtPointer call_data);
};

#endif // QUITDIALOG_H
