//
// Created by xy on 2024-06-04.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AddGoods.h" resolved

#include "addgoods.h"
#include "ui_AddGoods.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>

AddGoods::AddGoods(QWidget *parent) :
    QWidget(parent), ui(new Ui::AddGoods) {
  ui->setupUi(this);

  initWindow();

  connect(ui->addBtn,&QPushButton::clicked, this,&AddGoods::addGoods);
  connect(ui->clearBtn,&QPushButton::clicked, this,&AddGoods::clearData);
}


AddGoods::~AddGoods() {
  delete ui;
}
void AddGoods::initWindow() {
  setWindowTitle("添加商品");
  setFixedSize(this->width(), this->height());
  QPalette ple;
  ple.setColor(QPalette::Window,QColor(135,206,250));
  this->setPalette(ple);
}

void AddGoods::addGoods() {

  // 获取用户的输入
  QString goods_id = ui->goodsIdEdit->text();
  QString goods_name = ui->goodsNameEdit->text();
  QString goods_amount = ui->goodsCountEdit->text();
  QString goods_price = ui->goodsPriceEdit->text();
  QString supplier = ui->supplierEdit->text();
  QString director = ui->directorEdit->text();
  QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
  QString warehousetime = time;
  QString deliverytime =  time;
  QString remark = ui->remarkTextEdit->toPlainText();

  // 执行sql
  QString sql = QString("insert into goodsinfo (goods_id,goods_name,goods_amount,goods_price,supplier,director,warehousetime,deliverytime,remark) "
                        "values('%1','%2','%3','%4','%5','%6','%7','%8','%9')"
      ).arg(goods_id,goods_name,goods_amount,goods_price,supplier,director,warehousetime,deliverytime,remark);

  QSqlQuery sql_query;
  if(sql_query.exec(sql)){
    QMessageBox::information(this,"提示","插入成功");
  }else{
    QMessageBox::information(this,"提示","插入失败");
  }

  emit goodsAdd();
}
void AddGoods::clearData() {
  ui->goodsIdEdit->clear();
  ui->goodsNameEdit->clear();
  ui->goodsCountEdit->clear();
  ui->goodsPriceEdit->clear();
  ui->supplierEdit->clear();
  ui->directorEdit->clear();
  ui->remarkTextEdit->clear();
}

