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
  void addGoodsSql(const QString& query);
  //删除商品信息
  void removeGoodsSql(const QString& query);
  //修改商品信息
  void modifyGoodsSql(const QString& query);
  //查询商品信息
  void findGoodsSql(const QString& query);
 private:
  QSqlDatabase m_db;
  QSqlQuery m_query;
};

#endif //WAREHOUSEMANAGESYS__SQLCONNECT_H_
