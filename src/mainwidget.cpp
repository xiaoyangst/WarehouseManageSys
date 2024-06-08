#include "ui_mainwidget.h"
#include "mainwidget.h"
#include "SqlConnect.h"
#include "addgoods.h"
#include "ui_addgoods.h"
#include "uploadwarehouse.h"
#include "ui_uploadwarehouse.h"
#include "exportwarehouse.h"
#include "ui_exportwarehouse.h"
#include "summarydata.h"
#include "ui_summarydata.h"
#include "OpenXLSX.hpp"
#include <QFileDialog>
using namespace OpenXLSX;


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_db(new SqlConnect(this)),
    m_id("NULL"){

  ui->setupUi(this);

  initWindow();

  initSql();

  initConnectFunc();

  initTableWidget();

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
void MainWidget::initConnectFunc() {
  connect(ui->addGoodsBtn,&QPushButton::clicked, this,&MainWidget::addGoods);
  connect(ui->removeGoodsBtn,&QPushButton::clicked, this,&MainWidget::removeGoods);
  connect(ui->uploadWareHouseBtn,&QPushButton::clicked, this,&MainWidget::uploadWareHouse);
  connect(ui->exportWareHouseBtn,&QPushButton::clicked, this,&MainWidget::exportWareHouse);
  connect(ui->exportDataBtn,&QPushButton::clicked, this,&MainWidget::exportData);
  connect(ui->summeryDataBtn,&QPushButton::clicked, this,&MainWidget::summaryData);
  connect(ui->searchDataBtn,&QPushButton::clicked, this,&MainWidget::searchData);
  connect(ui->tableWidget,&QTableWidget::cellDoubleClicked, this,&MainWidget::updateId);
  connect(ui->showAllBtn,&QPushButton::clicked,this,&MainWidget::showAllDataToTable);
}

void MainWidget::initTableWidget() {
  // 设置 9 列 100 行
  ui->tableWidget->setColumnCount(9);
  ui->tableWidget->setRowCount(100);

  // 设置表不可被编辑
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  // 表头设置文本
  ui->tableWidget->setHorizontalHeaderLabels(
      QStringList() << tr("编号") << tr("名称") << tr("数量")
                    << tr("单价") << tr("供应商家") << tr("负责人")
                    << tr("入库时间") << tr("出库时间") << tr("备注"));

  // 设置表头字体和大小
  ui->tableWidget->horizontalHeader()->setFont(QFont(("宋体"),12));

  // 为每个文本的框设置合适的大小，有些框可能需要小一点，有些框可能需要大一点
  // 第一个参数代表列，第二个参数代表宽度
  ui->tableWidget->setColumnWidth(0, 80);
  ui->tableWidget->setColumnWidth(1, 150);
  ui->tableWidget->setColumnWidth(2, 80);
  ui->tableWidget->setColumnWidth(3, 80);
  ui->tableWidget->setColumnWidth(4, 300);
  ui->tableWidget->setColumnWidth(5, 80);
  ui->tableWidget->setColumnWidth(6, 200);
  ui->tableWidget->setColumnWidth(7, 200);
  ui->tableWidget->setColumnWidth(8, 180);

  // 显示数据库中所有的数据到表格中
  showAllDataToTable();
}

void MainWidget::addGoods() {
  auto *add_goods = new AddGoods();
  add_goods->show();
  connect(add_goods,&AddGoods::goodsAdd,this,&MainWidget::showAllDataToTable);
}
void MainWidget::removeGoods() {
  if (m_id.compare("NULL")){
    QMessageBox::StandardButton reply = QMessageBox::warning(this,"警告","确定要删除指定的商品？删除后不可恢复！！！",QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
      removeSingleGoods();
    }
  }else{
    QMessageBox::information(this, "提示", "没有选中任何商品，请选择之后再使用删除商品功能");
  }
}
void MainWidget::uploadWareHouse() {
  // 拿到id，传递给 UploadWareHouse对象
  if (m_id.compare("NULL")){
    auto *upload_ware_house = new UploadWareHouse(m_id);
    connect(upload_ware_house,&UploadWareHouse::warehouseUpdated, this,&MainWidget::showSingleDataToTable);
    upload_ware_house->show();
  }else{
    QMessageBox::information(this, "提示", "没有选中任何商品，请选择之后再使用入库功能");
  }
}
void MainWidget::exportWareHouse() {
  if (m_id.compare("NULL")){
    auto *export_ware_house = new ExportWareHouse(m_id);
    connect(export_ware_house,&ExportWareHouse::warehouseExported, this,&MainWidget::showSingleDataToTable);
    export_ware_house->show();
  }else{
    QMessageBox::information(this, "提示", "没有选中任何商品，请选择之后再使用出库功能");
  }
}
void MainWidget::exportData() {
  exportToExcel();
}
void MainWidget::summaryData() {
  auto *summary_data = new SummaryData();
  summary_data->show();
}

void MainWidget::searchData() {
  // 执行sql命令-从数据库中获取数据-在表格中展示数据
  QString id_ = ui->searchEdit->text();
  showSingleDataToTable(id_);
}
void MainWidget::updateId(int row, int column) {
  // 通过行和列来绝对确定商品的编号，而非除编号以外的其它数据
  m_id = ui->tableWidget->item(row,0)->data(0).toString();
}
void MainWidget::showAllDataToTable() {
  ui->tableWidget->clearContents();

  QString query_ = QString("select * from goodsinfo");
  m_sql_query.exec(query_);

  int row_ = 0;
  while (m_sql_query.next()){
    QString goods_id = m_sql_query.value(0).toString();
    QString goods_name = m_sql_query.value(1).toString();
    QString goods_amount = m_sql_query.value(2).toString();
    QString goods_price = m_sql_query.value(3).toString();
    QString supplier = m_sql_query.value(4).toString();
    QString director = m_sql_query.value(5).toString();
    QString warehousetime = m_sql_query.value(6).toString();
    QString deliverytime = m_sql_query.value(7).toString();
    QString remark = m_sql_query.value(8).toString();

    ui->tableWidget->setItem(row_,0,new QTableWidgetItem(goods_id));
    ui->tableWidget->setItem(row_,1,new QTableWidgetItem(goods_name));
    ui->tableWidget->setItem(row_,2,new QTableWidgetItem(goods_amount));
    ui->tableWidget->setItem(row_,3,new QTableWidgetItem(goods_price));
    ui->tableWidget->setItem(row_,4,new QTableWidgetItem(supplier));
    ui->tableWidget->setItem(row_,5,new QTableWidgetItem(director));
    ui->tableWidget->setItem(row_,6,new QTableWidgetItem(warehousetime));
    ui->tableWidget->setItem(row_,7,new QTableWidgetItem(deliverytime));
    ui->tableWidget->setItem(row_,8,new QTableWidgetItem(remark));

    row_++;
  }
}
void MainWidget::showSingleDataToTable(const QString& id) {
  ui->tableWidget->clearContents();   // 只清除表中数据，不清除表头内容

  QString query_ = QString("select * from goodsinfo where goods_id = %1").arg(id);
  m_sql_query.exec(query_);

  int row_ = 0;
  while (m_sql_query.next()){
    QString goods_id = m_sql_query.value(0).toString();
    QString goods_name = m_sql_query.value(1).toString();
    QString goods_amount = m_sql_query.value(2).toString();
    QString goods_price = m_sql_query.value(3).toString();
    QString supplier = m_sql_query.value(4).toString();
    QString director = m_sql_query.value(5).toString();
    QString warehousetime = m_sql_query.value(6).toString();
    QString deliverytime = m_sql_query.value(7).toString();
    QString remark = m_sql_query.value(8).toString();

    ui->tableWidget->setItem(row_,0,new QTableWidgetItem(goods_id));
    ui->tableWidget->setItem(row_,1,new QTableWidgetItem(goods_name));
    ui->tableWidget->setItem(row_,2,new QTableWidgetItem(goods_amount));
    ui->tableWidget->setItem(row_,3,new QTableWidgetItem(goods_price));
    ui->tableWidget->setItem(row_,4,new QTableWidgetItem(supplier));
    ui->tableWidget->setItem(row_,5,new QTableWidgetItem(director));
    ui->tableWidget->setItem(row_,6,new QTableWidgetItem(warehousetime));
    ui->tableWidget->setItem(row_,7,new QTableWidgetItem(deliverytime));
    ui->tableWidget->setItem(row_,8,new QTableWidgetItem(remark));

    row_++;
  }
}
void MainWidget::removeSingleGoods() {
    QString sql = QString("delete from goodsinfo where goods_id = %1").arg(m_id);
    if(!m_sql_query.exec(sql)){
      QMessageBox::information(this, "提示", "删除指定商品失败！！！");
    }
    showAllDataToTable();
}

void MainWidget::exportToExcel() {
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

  //  设置表头
  workspace.cell("A1").value() = "编号";
  workspace.cell("B1").value() = "名称";
  workspace.cell("C1").value() = "数量";
  workspace.cell("D1").value() = "单价";
  workspace.cell("E1").value() = "供应商家";
  workspace.cell("F1").value() = "负责人";
  workspace.cell("G1").value() = "入库时间";
  workspace.cell("H1").value() = "出库时间";
  workspace.cell("I1").value() = "备注";

  // 把数据写入到execl文件中
  QString query_ = QString("select * from goodsinfo");
  m_sql_query.exec(query_);

  int row_ = 2;
  while (m_sql_query.next()){
    QString goods_id = m_sql_query.value(0).toString();
    QString goods_name = m_sql_query.value(1).toString();
    QString goods_amount = m_sql_query.value(2).toString();
    QString goods_price = m_sql_query.value(3).toString();
    QString supplier = m_sql_query.value(4).toString();
    QString director = m_sql_query.value(5).toString();
    QString warehousetime = m_sql_query.value(6).toString();
    QString deliverytime = m_sql_query.value(7).toString();
    QString remark = m_sql_query.value(8).toString();

    workspace.cell("A"+QString::number(row_).toStdString()).value() = goods_id.toStdString();
    workspace.cell("B"+QString::number(row_).toStdString()).value() = goods_name.toStdString();
    workspace.cell("C"+QString::number(row_).toStdString()).value() = goods_amount.toStdString();
    workspace.cell("D"+QString::number(row_).toStdString()).value() = goods_price.toStdString();
    workspace.cell("E"+QString::number(row_).toStdString()).value() = supplier.toStdString();
    workspace.cell("F"+QString::number(row_).toStdString()).value() = director.toStdString();
    workspace.cell("G"+QString::number(row_).toStdString()).value() = warehousetime.toStdString();
    workspace.cell("H"+QString::number(row_).toStdString()).value() = deliverytime.toStdString();
    workspace.cell("I"+QString::number(row_).toStdString()).value() = remark.toStdString();

    row_++;
  }

  excelFile.save();
  excelFile.close();
}
