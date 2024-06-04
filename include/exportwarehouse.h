//
// Created by xy on 2024-06-04.
//

#ifndef WAREHOUSEMANAGESYS__EXPORTWAREHOUSE_H_
#define WAREHOUSEMANAGESYS__EXPORTWAREHOUSE_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ExportWareHouse; }
QT_END_NAMESPACE

class ExportWareHouse : public QWidget {
 Q_OBJECT

 public:
  explicit ExportWareHouse(QWidget *parent = nullptr);
  explicit ExportWareHouse(QString id,QWidget *parent = nullptr);
  ~ExportWareHouse() override;

 private:
  Ui::ExportWareHouse *ui;

  QString m_id;
};

#endif //WAREHOUSEMANAGESYS__EXPORTWAREHOUSE_H_
