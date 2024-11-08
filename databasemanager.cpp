#include "databasemanager.h"
#include "logmanager.h"

// 单例模式
DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}


// 连接数据库
bool DatabaseManager::connect(const QString &host, const int &port, const QString &database, const QString &username, const QString &password) {
    LogManager& logManager = LogManager::instance();
    qDebug() << QSqlDatabase::drivers();
    if (isConnected) {
        logManager.log(LOG_DATABASE, WARNING, "数据库已被连接");
    }

    db.setHostName(host);
    db.setDatabaseName(database);
    db.setUserName(username);
    db.setPassword(password);
    db.setPort(port);

    if (!db.open()) {
        logManager.log(LOG_DATABASE, ERROR, "数据库连接失败");
        return false;
    }

    isConnected = true;
    logManager.log(LOG_DATABASE, INFO, "数据库成功连接，连接至 " + db.databaseName() + " 数据库");
    return true;
}

// 断开数据库连接
void DatabaseManager::disconnect() {
    LogManager& logManager = LogManager::instance();
    if (isConnected) {
        db.close();
        isConnected = false;
        logManager.log(LOG_DATABASE, INFO, "数据库连接已断开");
    }
}

// 非查询语句
bool DatabaseManager::execute(const QString &queryStr) {
    LogManager& logManager = LogManager::instance();
    if (!isConnected) {
        logManager.log(LOG_DATABASE, ERROR, "数据库未连接");
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        logManager.log(LOG_DATABASE, WARNING, "数据库查询失败");
        return false;
    }

    logManager.log(LOG_DATABASE, INFO, "数据库查询成功");
    return true;
}

// 数据库查询
QSqlQuery DatabaseManager::select(const QString &queryStr) {
    LogManager& logManager = LogManager::instance();
    if (!isConnected) {
        logManager.log(LOG_DATABASE, ERROR, "数据库未连接");
        return QSqlQuery();
    }

    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        logManager.log(LOG_DATABASE, WARNING, "数据库查询失败");
    }

    logManager.log(LOG_DATABASE, INFO, "数据库查询成功");
    return query;
}

// 构造函数
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent), isConnected(false) {
    // 数据库驱动器：MySQL
    db = QSqlDatabase::addDatabase("QMYSQL");
}

// 析构函数
DatabaseManager::~DatabaseManager() {
    disconnect();
}