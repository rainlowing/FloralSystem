#include "global.h"
#include <QApplication>

// 应用程序全局设置
QFont Global::appFont = QFont("微软雅黑", 10);

// 使用全局设置
void Global::initStyle() {
    QApplication::setFont(appFont);
}


// 数据库配置
QString Global::sqlHost = "127.0.0.1";
QString Global::sqlUserName = "root";
QString Global::sqlPassword = "123456";
QString Global::sqlDatabase = "test";
int Global::sqlPort = 3306;