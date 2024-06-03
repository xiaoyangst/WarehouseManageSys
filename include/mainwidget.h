//
// Created by xy on 2024-06-02.
//

#ifndef WAREHOUSEMANAGESYS__MAINWIDGET_H_
#define WAREHOUSEMANAGESYS__MAINWIDGET_H_

#include <QWidget>
#include "SqlConnect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget {
 Q_OBJECT

 public:
  explicit MainWidget(QWidget *parent = nullptr);
  ~MainWidget() override;
 private:
  void initWindow();
  void initSql();
 private:
  Ui::MainWidget *ui;

  SqlConnect* m_db;
};

#endif //WAREHOUSEMANAGESYS__MAINWIDGET_H_
