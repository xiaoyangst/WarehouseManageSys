#include <QApplication>
#include "mainwidget.h"
#include <QFile>

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
  MainWidget main_widget;
  main_widget.show();

  return QApplication::exec();
}
