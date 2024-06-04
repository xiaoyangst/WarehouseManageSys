//
// Created by xy on 2024-06-04.
//

#ifndef WAREHOUSEMANAGESYS__ADDGOODS_H_
#define WAREHOUSEMANAGESYS__ADDGOODS_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AddGoods; }
QT_END_NAMESPACE

class AddGoods : public QWidget {
 Q_OBJECT

 public:
  explicit AddGoods(QWidget *parent = nullptr);
  ~AddGoods() override;
 private:
  void initWindow();
 private slots:
  void addGoods();
 private:
  Ui::AddGoods *ui;
};

#endif //WAREHOUSEMANAGESYS__ADDGOODS_H_
