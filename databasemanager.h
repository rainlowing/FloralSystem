// 数据库管理类
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class DatabaseManager : public QObject {
public:
    // 单例模式
    static DatabaseManager& instance();
    // 连接数据库
    bool connect(const QString &host, const int &port, const QString &database, const QString &username, const QString &password);
    // 断开数据库连接
    void disconnect();
    // 非查询语句
    bool execute(const QString &queryStr);
    // 查询数据库
    QSqlQuery select(const QString &queryStr);

private:
    DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    QSqlDatabase db;
    bool isConnected; 
};

#endif // DATABASEMANAGER_H 