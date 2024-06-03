#ifndef WAREHOUSEMANAGESYS__SQLCONNECT_H_
#define WAREHOUSEMANAGESYS__SQLCONNECT_H_

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

class SqlConnect : public QWidget{
  Q_OBJECT
 public:
  explicit SqlConnect(QWidget* parent = nullptr);
  ~SqlConnect();

  // 连接数据库
  bool connectDb(const QString& user, const QString& pwd, const QString& host, const QString& db, int port = 3306);
  //增加商品信息
  void addGoods();
  //删除商品信息
  void removeGoods();
  //修改商品信息
  void modifyGoods();
  //查询商品信息
  void findGoods();
 private:
  QSqlDatabase m_db;
};

#endif //WAREHOUSEMANAGESYS__SQLCONNECT_H_
