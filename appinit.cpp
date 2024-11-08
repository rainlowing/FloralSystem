#include "appinit.h"
#include "logmanager.h"
#include "databasemanager.h"
#include "global.h"
#include <QMutex>
#include <QMutexLocker>
#include <QApplication>
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QMessageBox>

// 单例模式
AppInit* AppInit::instance = nullptr;
AppInit* AppInit::getInstance() {
    if (!instance) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!instance) {
            instance = new AppInit();
        }
    }

    return instance;
}

// 构造函数
AppInit::AppInit(QObject *parent) : QObject(parent) {

}

// 事件过滤器
bool AppInit::eventFilter(QObject *watched, QEvent *event) {
    // QWidget *widget = qobject_cast<QWidget *>(watched);
    // if (widget->property("canMove").toBool() == false) {
    //     return QObject::eventFilter(watched,event);
    // } 

    // // 处理窗口拖动事件
    // static QPoint mousePoint;
    // static bool mousePressed = false;

    // QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    // if (event->type() == QEvent::MouseButtonPress) {
    //     if (mouseEvent->button() == Qt::LeftButton) {
    //         mousePressed = true;
    //         mousePoint = mouseEvent->globalPos() - widget->pos();
    //         return true;
    //     }
    // } else if (mouseEvent->type() == QEvent::MouseButtonRelease) {
    //     mousePressed = false;
    //     qDebug() << "mousePoint:" << mousePoint;
    //     return true;
    // } else if (mouseEvent->type() == QEvent::MouseMove) {
    //     if (mousePressed && (mouseEvent->buttons() & Qt::LeftButton)) {
    //         widget->move(mouseEvent->globalPos() - mousePoint);
    //         return true;
    //     }
    // }

    return QObject::eventFilter(watched, event);

}

// 应用程序初始化，返回 false 表示初始化失败
bool AppInit::init() {
    LogManager& logManager = LogManager::instance();

    // 安装事件过滤器
    qApp->installEventFilter(this);

    // 初始化全局样式
    Global::initStyle();

    // 初始化日志管理器
    logManager.log(LOG_APPLICATION, DEBUG, "应用程序初始化成功");

    // 初始化数据库
    DatabaseManager& dbm = DatabaseManager::instance();
    bool success = dbm.connect(Global::sqlHost, Global::sqlPort, Global::sqlDatabase, Global::sqlUserName, Global::sqlPassword);
    if (!success) {
        // 数据库连接失败，程序退出
        logManager.log(LOG_APPLICATION, ERROR, "数据库连接失败，程序自动退出");
        QMessageBox::warning(nullptr, "错误", "数据库连接失败", QMessageBox::Ok);
        return false;
    }

    // 初始化网络

    return true;
}