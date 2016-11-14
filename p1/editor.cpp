#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include "mainwindow.h"

int main(int argc, char **argv)
{
  MainWindow *mw = new MainWindow(argc, argv);
  mw->run();
  return 0;
}
