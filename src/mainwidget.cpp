#include "ui_mainwidget.h"
#include "mainwidget.h"
#include "SqlConnect.h"
#include "addgoods.h"
#include "ui_addgoods.h"
#include "uploadwarehouse.h"
#include "ui_uploadwarehouse.h"
#include "exportwarehouse.h"
#include "ui_exportwarehouse.h"
#include "exportwarehouse.h"
#include "ui_exportwarehouse.h"


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

}
void MainWidget::summaryData() {

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

  QSqlQuery sql_query;
  QString query_ = QString("select * from goodsinfo");
  sql_query.exec(query_);

  int row_ = 0;
  while (sql_query.next()){
    QString goods_id = sql_query.value(0).toString();
    QString goods_name = sql_query.value(1).toString();
    QString goods_amount = sql_query.value(2).toString();
    QString goods_price = sql_query.value(3).toString();
    QString supplier = sql_query.value(4).toString();
    QString director = sql_query.value(5).toString();
    QString warehousetime = sql_query.value(6).toString();
    QString deliverytime = sql_query.value(7).toString();
    QString remark = sql_query.value(8).toString();

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

  QSqlQuery sql_query;

  QString query_ = QString("select * from goodsinfo where goods_id = %1").arg(id);
  sql_query.exec(query_);

  int row_ = 0;
  while (sql_query.next()){
    QString goods_id = sql_query.value(0).toString();
    QString goods_name = sql_query.value(1).toString();
    QString goods_amount = sql_query.value(2).toString();
    QString goods_price = sql_query.value(3).toString();
    QString supplier = sql_query.value(4).toString();
    QString director = sql_query.value(5).toString();
    QString warehousetime = sql_query.value(6).toString();
    QString deliverytime = sql_query.value(7).toString();
    QString remark = sql_query.value(8).toString();

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
