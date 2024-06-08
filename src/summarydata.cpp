#include <QSqlQuery>
#include "summarydata.h"
#include "ui_SummaryData.h"
#include "OpenXLSX.hpp"
#include <QFileDialog>
#include <QMessageBox>
using namespace OpenXLSX;

QString execl_data[] = {
    "A","B","C","D","E","F","G","H","I","J","K"
};

SummaryData::SummaryData(QWidget *parent) :
    QWidget(parent), ui(new Ui::SummaryData) {
  ui->setupUi(this);

  initWindow();
  summaryPrice();

  connect(ui->goodsBtn,&QPushButton::clicked,this,&SummaryData::summaryPrice);
  connect(ui->inBtn,&QPushButton::clicked,this,&SummaryData::summaryIn);
  connect(ui->outBtn,&QPushButton::clicked,this,&SummaryData::summaryOut);
  connect(ui->saveBtn,&QPushButton::clicked,this,&SummaryData::saveData);

}

SummaryData::~SummaryData() {
  delete ui;
}
void SummaryData::initWindow() {
  setWindowTitle("数据汇总");
  setFixedSize(this->width(), this->height());
  QPalette ple;
  ple.setColor(QPalette::Window, QColor(135, 206, 250));
  this->setPalette(ple);
}
void SummaryData::summaryPrice() {
  initPriceWindow();
  showPriceToTable();
}
void SummaryData::summaryIn() {
  initInWindow();
  showInToTable();
}
void SummaryData::summaryOut() {
  initOutWindow();
  showOutToTable();
}
void SummaryData::saveData() {

  // 读取表格中的数据，加入到execl表格中
  int rowCount = ui->tableWidget->rowCount();
  int columnCount = ui->tableWidget->columnCount();

  // 确定保存的文件绝对路径
  QString selectedPath = QFileDialog::getExistingDirectory(this, "Select Directory", "/home");
  if (selectedPath.isEmpty()) {
    QMessageBox::information(this, "提示", "没有选中合适的路径！！！");
    return;
  }

  // 设置命名
  QString curTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hhmmss");

  // 合并路径+文件名
  QString filename = selectedPath + "/" + curTime + ".xlsx";

  // 创建execl文件
  XLDocument excelFile;
  excelFile.create(filename.toStdString());
  auto workspace = excelFile.workbook().worksheet("Sheet1");

  // 获取表头数据并设置
  int headerCount = ui->tableWidget->columnCount();
  for (int column = 0; column < headerCount; ++column) {
    QTableWidgetItem* headerItem = ui->tableWidget->horizontalHeaderItem(column);
    if (headerItem) {
      QString headerText = headerItem->text();
      workspace.cell(execl_data[column].toStdString() + "1").value() = headerText.toStdString();
    } else {
      break;
    }
  }

  for (int row = 0; row < rowCount; row++) {   // 行
    for (int column = 0; column < columnCount; column++) {  // 列
      QTableWidgetItem* item = ui->tableWidget->item(row, column);
      if (item) {
        QString cellData = item->text();
        workspace.cell(execl_data[column].toStdString() + QString::number(row+2).toStdString()).value() = cellData.toStdString();
      } else {
        break;
      }
    }
  }

  excelFile.save();
  excelFile.close();
}
void SummaryData::initPriceWindow() {
  // 设置 8  列 100 行
  ui->tableWidget->setColumnCount(8);
  ui->tableWidget->setRowCount(100);

  // 设置表不可被编辑
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  // 表头设置文本
  ui->tableWidget->setHorizontalHeaderLabels(
      QStringList() << tr("编号") << tr("名称") << tr("数量")
                    << tr("单价") << tr("总价") << tr("供应商家") << tr("负责人")
                    << tr("备注"));

  // 设置表头字体和大小
  ui->tableWidget->horizontalHeader()->setFont(QFont(("宋体"),12));

  // 为每个文本的框设置合适的大小，有些框可能需要小一点，有些框可能需要大一点
  // 第一个参数代表列，第二个参数代表宽度
  ui->tableWidget->setColumnWidth(0, 80);
  ui->tableWidget->setColumnWidth(1, 150);
  ui->tableWidget->setColumnWidth(2, 80);
  ui->tableWidget->setColumnWidth(3, 80);
  ui->tableWidget->setColumnWidth(4, 130);
  ui->tableWidget->setColumnWidth(5, 80);
  ui->tableWidget->setColumnWidth(6, 80);
  ui->tableWidget->setColumnWidth(8, 180);
}
void SummaryData::initInWindow() {
  // 设置 8  列 100 行
  ui->tableWidget->setColumnCount(8);
  ui->tableWidget->setRowCount(100);

  // 设置表不可被编辑
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  // 表头设置文本
  ui->tableWidget->setHorizontalHeaderLabels(
      QStringList() << tr("编号") << tr("名称") << tr("数量")
                    << tr("单价") << tr("入库总量") << tr("供应商家") << tr("负责人")
                    << tr("备注"));

  // 设置表头字体和大小
  ui->tableWidget->horizontalHeader()->setFont(QFont(("宋体"),12));

  // 为每个文本的框设置合适的大小，有些框可能需要小一点，有些框可能需要大一点
  // 第一个参数代表列，第二个参数代表宽度
  ui->tableWidget->setColumnWidth(0, 80);
  ui->tableWidget->setColumnWidth(1, 150);
  ui->tableWidget->setColumnWidth(2, 80);
  ui->tableWidget->setColumnWidth(3, 80);
  ui->tableWidget->setColumnWidth(4, 130);
  ui->tableWidget->setColumnWidth(5, 80);
  ui->tableWidget->setColumnWidth(6, 80);
  ui->tableWidget->setColumnWidth(8, 180);
}
void SummaryData::initOutWindow() {
  // 设置 8  列 100 行
  ui->tableWidget->setColumnCount(8);
  ui->tableWidget->setRowCount(100);

  // 设置表不可被编辑
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  // 表头设置文本
  ui->tableWidget->setHorizontalHeaderLabels(
      QStringList() << tr("编号") << tr("名称") << tr("数量")
                    << tr("单价") << tr("出库总量") << tr("供应商家") << tr("负责人")
                    << tr("备注"));

  // 设置表头字体和大小
  ui->tableWidget->horizontalHeader()->setFont(QFont(("宋体"),12));

  // 为每个文本的框设置合适的大小，有些框可能需要小一点，有些框可能需要大一点
  // 第一个参数代表列，第二个参数代表宽度
  ui->tableWidget->setColumnWidth(0, 80);
  ui->tableWidget->setColumnWidth(1, 150);
  ui->tableWidget->setColumnWidth(2, 80);
  ui->tableWidget->setColumnWidth(3, 80);
  ui->tableWidget->setColumnWidth(4, 130);
  ui->tableWidget->setColumnWidth(5, 80);
  ui->tableWidget->setColumnWidth(6, 80);
  ui->tableWidget->setColumnWidth(8, 180);
}
void SummaryData::showPriceToTable() {
  ui->tableWidget->clearContents();

  QSqlQuery m_sql_query;
  QSqlQuery h_sql_query;

  QString m_query = QString("select * from goodsinfo");
  m_sql_query.exec(m_query);
  int row_ = 0;
  while (m_sql_query.next()){

    QString goods_id = m_sql_query.value(0).toString();
    QString goods_name = m_sql_query.value(1).toString();
    QString goods_amount = m_sql_query.value(2).toString();
    QString goods_price = m_sql_query.value(3).toString();
    QString supplier = m_sql_query.value(4).toString();
    QString director = m_sql_query.value(5).toString();
    QString remark = m_sql_query.value(8).toString();

    ui->tableWidget->setItem(row_,0,new QTableWidgetItem(goods_id));
    ui->tableWidget->setItem(row_,1,new QTableWidgetItem(goods_name));
    ui->tableWidget->setItem(row_,2,new QTableWidgetItem(goods_amount));
    ui->tableWidget->setItem(row_,3,new QTableWidgetItem(goods_price));
    ui->tableWidget->setItem(row_,5,new QTableWidgetItem(supplier));
    ui->tableWidget->setItem(row_,6,new QTableWidgetItem(director));
    ui->tableWidget->setItem(row_,7,new QTableWidgetItem(remark));

    // 显示当前已有数量商品对应的总价

    QString h_query = QString("select total_price from totalprice where goods_id = %1").arg(goods_id);
    h_sql_query.exec(h_query);
    if (h_sql_query.next()){
      QString total_price = h_sql_query.value(0).toString();
      ui->tableWidget->setItem(row_,4,new QTableWidgetItem(total_price));
    }


    row_++;
  }
}
void SummaryData::showInToTable() {
  ui->tableWidget->clearContents();

  QSqlQuery m_sql_query;
  QSqlQuery h_sql_query;

  QString m_query = QString("select * from goodsinfo");
  m_sql_query.exec(m_query);
  int row_ = 0;
  while (m_sql_query.next()){

    QString goods_id = m_sql_query.value(0).toString();
    QString goods_name = m_sql_query.value(1).toString();
    QString goods_amount = m_sql_query.value(2).toString();
    QString goods_price = m_sql_query.value(3).toString();
    QString supplier = m_sql_query.value(4).toString();
    QString director = m_sql_query.value(5).toString();
    QString remark = m_sql_query.value(8).toString();

    ui->tableWidget->setItem(row_,0,new QTableWidgetItem(goods_id));
    ui->tableWidget->setItem(row_,1,new QTableWidgetItem(goods_name));
    ui->tableWidget->setItem(row_,2,new QTableWidgetItem(goods_amount));
    ui->tableWidget->setItem(row_,3,new QTableWidgetItem(goods_price));
    ui->tableWidget->setItem(row_,5,new QTableWidgetItem(supplier));
    ui->tableWidget->setItem(row_,6,new QTableWidgetItem(director));
    ui->tableWidget->setItem(row_,7,new QTableWidgetItem(remark));

    // 显示总入库数量
    QString h_query = QString("select in_count from goodsininfo where goods_id = %1").arg(goods_id);
    h_sql_query.exec(h_query);
    if (h_sql_query.next()){
      QString in_count = h_sql_query.value(0).toString();
      ui->tableWidget->setItem(row_,4,new QTableWidgetItem(in_count));
    }

    row_++;
  }
}
void SummaryData::showOutToTable() {
  ui->tableWidget->clearContents();

  QSqlQuery m_sql_query;
  QSqlQuery h_sql_query;

  QString m_query = QString("select * from goodsinfo");
  m_sql_query.exec(m_query);
  int row_ = 0;
  while (m_sql_query.next()){

    QString goods_id = m_sql_query.value(0).toString();
    QString goods_name = m_sql_query.value(1).toString();
    QString goods_amount = m_sql_query.value(2).toString();
    QString goods_price = m_sql_query.value(3).toString();
    QString supplier = m_sql_query.value(4).toString();
    QString director = m_sql_query.value(5).toString();
    QString remark = m_sql_query.value(8).toString();

    ui->tableWidget->setItem(row_,0,new QTableWidgetItem(goods_id));
    ui->tableWidget->setItem(row_,1,new QTableWidgetItem(goods_name));
    ui->tableWidget->setItem(row_,2,new QTableWidgetItem(goods_amount));
    ui->tableWidget->setItem(row_,3,new QTableWidgetItem(goods_price));
    ui->tableWidget->setItem(row_,5,new QTableWidgetItem(supplier));
    ui->tableWidget->setItem(row_,6,new QTableWidgetItem(director));
    ui->tableWidget->setItem(row_,7,new QTableWidgetItem(remark));

    // 显示总出库数量
    QString h_query = QString("select out_count from goodsoutinfo where goods_id = %1").arg(goods_id);
    h_sql_query.exec(h_query);
    if (h_sql_query.next()){
      QString out_count = h_sql_query.value(0).toString();
      ui->tableWidget->setItem(row_,4,new QTableWidgetItem(out_count));
    }

    row_++;
  }
}
