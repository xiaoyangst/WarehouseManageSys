
#ifndef WAREHOUSEMANAGESYS__MAINWIDGET_H_
#define WAREHOUSEMANAGESYS__MAINWIDGET_H_

#include <QWidget>
#include <QTableWidgetItem>
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
  void initConnectFunc();
  void initTableWidget();
  void showSingleDataToTable(const QString& id);
  void showAllDataToTable();
  void removeSingleGoods();
  void exportToExcel();
 private slots:
  void addGoods();
  void removeGoods();
  void uploadWareHouse();
  void exportWareHouse();
  void exportData();
  void summaryData();
  void searchData();
  void updateId(int row, int column);
 private:
  Ui::MainWidget *ui;
  QString m_id;
  SqlConnect* m_db;
  QSqlQuery m_sql_query;
};

#endif //WAREHOUSEMANAGESYS__MAINWIDGET_H_
