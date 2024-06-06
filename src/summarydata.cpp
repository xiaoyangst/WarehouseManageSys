//
// Created by xy on 2024-06-06.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SummaryData.h" resolved

#include "summarydata.h"
#include "ui_SummaryData.h"

SummaryData::SummaryData(QWidget *parent) :
    QWidget(parent), ui(new Ui::SummaryData) {
  ui->setupUi(this);
}

SummaryData::~SummaryData() {
  delete ui;
}
