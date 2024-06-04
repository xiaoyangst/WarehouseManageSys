
#include "SqlConnect.h"

SqlConnect::SqlConnect(QWidget* parent)
  :m_db(QSqlDatabase::addDatabase("QODBC"))
{

}
SqlConnect::~SqlConnect() {
  m_db.close();
}
bool SqlConnect::connectDb(const QString &user, const QString &pwd, const QString &host, const QString &db, int port) {

  m_db.setUserName(user);
  m_db.setPassword(pwd);
  m_db.setHostName(host);
  m_db.setDatabaseName(db);
  m_db.setPort(port);

  return m_db.open();
}
void SqlConnect::addGoodsSql(const QString& query) {

}
void SqlConnect::removeGoodsSql(const QString& query) {

}
void SqlConnect::modifyGoodsSql(const QString& query) {

}
void SqlConnect::findGoodsSql(const QString& query) {

}

