//
// Created by xy on 2024-06-05.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RemoveGoods.h" resolved

#include "removegoods.h"
#include "ui_RemoveGoods.h"

RemoveGoods::RemoveGoods(QWidget *parent) :
    QWidget(parent), ui(new Ui::RemoveGoods) {
  ui->setupUi(this);
}

RemoveGoods::~RemoveGoods() {
  delete ui;
}
