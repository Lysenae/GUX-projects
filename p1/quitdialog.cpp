#include "quitdialog.h"

Widget QuitDialog::m_quit_dialog = 0;
bool QuitDialog::m_rslt          = false;
bool QuitDialog::m_up            = false;

QuitDialog::QuitDialog(Widget parent)
{
  m_quit_dialog = XmCreateQuestionDialog(parent, (char*)"quitDialog", NULL, 0);
  m_msg         = XmStringCreateSimple((char*)"Quit application?");
  m_quit        = XmStringCreateSimple((char*)"Quit");
  m_cancel      = XmStringCreateSimple((char*)"Cancel");

  XtVaSetValues(
    m_quit_dialog,
    XmNmessageString, m_msg,
    XmNokLabelString, m_quit,
    XmNcancelLabelString, m_cancel,
    XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
    NULL
  );
  XtAddCallback(m_quit_dialog, XmNokCallback, OnQuitClicked, NULL);
  XtAddCallback(m_quit_dialog, XmNcancelCallback, OnCancelClicked, NULL);
}

QuitDialog::~QuitDialog()
{
  XmStringFree(m_msg);
  XmStringFree(m_quit);
  XmStringFree(m_cancel);
}

void QuitDialog::Show()
{
  XtManageChild(m_quit_dialog);
  XtPopup(XtParent(m_quit_dialog), XtGrabNone);
}

bool QuitDialog::Result()
{
  while(m_up){}
  return m_rslt;
}

void QuitDialog::OnQuitClicked(Widget w, XtPointer client_data,
XtPointer call_data)
{
  m_rslt = true;
}

void QuitDialog::OnCancelClicked(Widget w, XtPointer client_data,
XtPointer call_data)
{
  m_rslt = false;
}
