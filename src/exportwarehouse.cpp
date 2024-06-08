
#include "exportwarehouse.h"

#include <utility>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDateTime>
#include "ui_ExportWareHouse.h"

ExportWareHouse::ExportWareHouse(QWidget *parent) {

}

ExportWareHouse::ExportWareHouse(QString id, QWidget *parent) :
    QWidget(parent), ui(new Ui::ExportWareHouse), m_id(std::move(id)) {
  ui->setupUi(this);

  initWindow();

  connect(ui->exportBtn, &QPushButton::clicked, this, &ExportWareHouse::exportWareHouse);
  connect(ui->clearBtn, &QPushButton::clicked, this, &ExportWareHouse::clearData);
}

ExportWareHouse::~ExportWareHouse() {
  delete ui;
}

void ExportWareHouse::initWindow() {
  setWindowTitle("商品出库");
  setFixedSize(this->width(), this->height());
  QPalette ple;
  ple.setColor(QPalette::Window, QColor(135, 206, 250));
  this->setPalette(ple);

  showGoodsId();
}
void ExportWareHouse::showGoodsId() {
  ui->Countlabel->setText(m_id);
}
void ExportWareHouse::clearData() {
  ui->CountEdit->clear();
}
void ExportWareHouse::exportWareHouse() {
  //先获取表中该商品已有数量
  QSqlQuery sql_query;
  QString id_ = m_id;
  QString query_ = QString("select goods_amount,goods_price from goodsinfo where goods_id = %1").arg(id_);
  if(!sql_query.exec(query_)){
    QMessageBox::information(this, "提示", "查询商品数量失败");
    return;
  }

  //再获取用户数量与之求和--把最新的数据更新即可
  int new_total_price = 0;
  if (sql_query.next()) {
    int num = sql_query.value(0).toInt() - ui->CountEdit->text().toInt();
    new_total_price = num * sql_query.value(1).toInt();
    if (num < 0) {
      QMessageBox::information(this, "提示", "出库数量超过已有库存！！！");
      clearData();
      return;
    }
    QString numStr = QString::number(num);    // int  --》  QString
    query_ = QString("update goodsinfo set goods_amount = %1 where goods_id = %2").arg(numStr, id_);
    if (sql_query.exec(query_)) {
      QMessageBox::information(this, "提示", "出库成功");
    } else {
      QMessageBox::information(this, "提示", "出库失败");
    }
  }

  // 更新入库时间
  QString newDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
  // 字符串的占位符需要用 '' 包裹，如果是数字可以不用
  query_ = QString("update goodsinfo set deliverytime = '%1' where goods_id = %2").arg(newDate, id_);
  if (!sql_query.exec(query_)) {
    QMessageBox::information(this, "提示", "更新出库时间失败");
  }

  // 出库数量记录到goodsoutinfo表中
  query_ = QString("select out_count from goodsoutinfo where goods_id = %1").arg(id_);
  if (!sql_query.exec(query_)) {
    QMessageBox::information(this, "提示", "查询出库数量记录失败！！！");
  }else{
    if(sql_query.next()){
      int count = sql_query.value(0).toInt() + ui->CountEdit->text().toInt();
      QString newCount = QString::number(count);
      qDebug()<<newCount;
      query_ = QString("update goodsoutinfo set out_count = '%1' where goods_id = %2").arg(newCount, id_);
      if (!sql_query.exec(query_)){
        QMessageBox::information(this, "提示", "出库总数量记录失败！！！");
      }
    }
  }

  // 更新 totalprice表中的总价记录
  query_ = QString("update totalprice set total_price = '%1' where goods_id = %2").arg(QString::number(new_total_price),id_);
  if (!sql_query.exec(query_)) {
    QMessageBox::information(this, "提示", "更新总价记录失败！！！");
  }


  emit warehouseExported(id_);
}
