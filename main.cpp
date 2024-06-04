#include <QApplication>
#include "mainwidget.h"


int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  MainWidget main_widget;
  main_widget.show();

  return QApplication::exec();
}
