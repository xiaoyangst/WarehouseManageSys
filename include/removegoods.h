//
// Created by xy on 2024-06-05.
//

#ifndef WAREHOUSEMANAGESYS__REMOVEGOODS_H_
#define WAREHOUSEMANAGESYS__REMOVEGOODS_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RemoveGoods; }
QT_END_NAMESPACE

class RemoveGoods : public QWidget {
 Q_OBJECT

 public:
  explicit RemoveGoods(QWidget *parent = nullptr);
  ~RemoveGoods() override;

 private:
  Ui::RemoveGoods *ui;
};

#endif //WAREHOUSEMANAGESYS__REMOVEGOODS_H_
