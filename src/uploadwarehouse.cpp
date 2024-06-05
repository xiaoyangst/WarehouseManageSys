
#include "uploadwarehouse.h"

#include <utility>
#include <QDateTime>
#include "ui_UploadWareHouse.h"
UploadWareHouse::UploadWareHouse(QWidget *parent) {

}
UploadWareHouse::UploadWareHouse(QString id, QWidget *parent) :
    QWidget(parent), ui(new Ui::UploadWareHouse), m_id(std::move(id)) {
  ui->setupUi(this);

  initWindow();

  connect(ui->uploadBtn, &QPushButton::clicked, this, &UploadWareHouse::uploadWareHouse);
  connect(ui->cloaseBtn, &QPushButton::clicked, this, &UploadWareHouse::clearData);
}

UploadWareHouse::~UploadWareHouse() {
  delete ui;
}
void UploadWareHouse::initWindow() {
  setWindowTitle("商品入库");
  setFixedSize(this->width(), this->height());
  QPalette ple;
  ple.setColor(QPalette::Window, QColor(135, 206, 250));
  this->setPalette(ple);

  showGoodsId();
}

void UploadWareHouse::uploadWareHouse() {
  //先获取表中该商品已有数量
  QSqlQuery sql_query;

  QString id_ = m_id;
  QString query_ = QString("select goods_amount from goodsinfo where goods_id = %1").arg(id_);
  sql_query.exec(query_);

  //再获取用户数量与之求和-把最新的数据更新即可
  if (sql_query.next()) {
    int num = ui->countEdit->text().toInt() + sql_query.value(0).toInt();
    QString numStr = QString::number(num);    // int  --》  QString
    query_ = QString("update goodsinfo set goods_amount = %1 where goods_id = %2").arg(numStr, id_);
    if (sql_query.exec(query_)) {
      QMessageBox::information(this, "提示", "入库成功");
    } else {
      QMessageBox::information(this, "提示", "入库失败");
    }
  }

  // 更新入库时间
  QString newDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
  // 字符串的占位符需要用 '' 包裹，如果是数字可以不用
  query_ = QString("update goodsinfo set warehousetime = '%1' where goods_id = %2").arg(newDate,id_);
  if(!sql_query.exec(query_)){
    QMessageBox::information(this, "提示", "更新入库时间失败");
  }

  emit warehouseUpdated(id_);
}
void UploadWareHouse::showGoodsId() {
  ui->showLabel->setText(m_id);
}
void UploadWareHouse::clearData() {
  ui->countEdit->clear();
}


