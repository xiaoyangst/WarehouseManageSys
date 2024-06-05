
#ifndef WAREHOUSEMANAGESYS__UPLOADWAREHOUSE_H_
#define WAREHOUSEMANAGESYS__UPLOADWAREHOUSE_H_

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include "mainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UploadWareHouse; }
QT_END_NAMESPACE

class UploadWareHouse : public QWidget {
 Q_OBJECT

 public:
  explicit UploadWareHouse(QWidget *parent = nullptr);
  explicit UploadWareHouse(QString id,QWidget *parent = nullptr);
  ~UploadWareHouse() override;
 signals:
  void warehouseUpdated(const QString &id);
 private:
  void initWindow();
  void showGoodsId();
 private slots:
  void uploadWareHouse();
  void clearData();
 private:
  Ui::UploadWareHouse *ui;
  QString m_id;
};

#endif //WAREHOUSEMANAGESYS__UPLOADWAREHOUSE_H_
