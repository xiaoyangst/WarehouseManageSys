#include "ui_mainwidget.h"
#include "mainwidget.h"
#include "SqlConnect.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_db(new SqlConnect(this)) {

  ui->setupUi(this);

  initWindow();

  initSql();

}

MainWidget::~MainWidget() {
  delete ui;
}
void MainWidget::initSql() {
  if (!m_db->connectDb("root", "root", "127.0.0.1", "warehouse")) {
    QMessageBox::information(this, "提示", "连接失败");
  }
}
void MainWidget::initWindow() {
  setWindowTitle("库存管理系统");
  setFixedSize(this->width(), this->height());
  QPalette ple;
  ple.setColor(QPalette::Window,QColor(135,206,250));
  this->setPalette(ple);
}
