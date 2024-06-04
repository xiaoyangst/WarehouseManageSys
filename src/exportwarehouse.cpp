//
// Created by xy on 2024-06-04.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExportWareHouse.h" resolved

#include "exportwarehouse.h"
#include "ui_ExportWareHouse.h"

ExportWareHouse::ExportWareHouse(QString id,QWidget *parent) :
    QWidget(parent), ui(new Ui::ExportWareHouse),m_id(id) {
  ui->setupUi(this);
}

ExportWareHouse::~ExportWareHouse() {
  delete ui;
}
ExportWareHouse::ExportWareHouse(QWidget *parent) {

}
