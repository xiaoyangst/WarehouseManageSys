#include <QApplication>
#include "mainwidget.h"
#include <QFile>

#include "OpenXLSX.hpp"
using namespace OpenXLSX;

void test() {
  XLDocument doc;
  doc.create("E:/Fl/b.xlsx");
  doc.save();
  doc.close();
}


void loadQss(QApplication &application){
  QFile file(":/qss/style.qss");
  if (file.open(QFile::ReadOnly)){
    QString styleSheet = QLatin1String(file.readAll());
    application.setStyleSheet(styleSheet);
    file.close();
  }
}

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  loadQss(a);
  //test();
  MainWidget main_widget;
  main_widget.show();

  return QApplication::exec();
}
