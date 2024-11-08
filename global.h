// 全局配置类
#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QFont>

class Global {
public:
    // 应用程序全局设置
    static QString appVersion;          // 应用程序版本号
    static QString appTitle;            // 应用程序标题
    static QString appIcon;             // 应用程序图标
    static QFont appFont;               // 应用程序字体

    // 使用全局设置
    static void initStyle();

    // 数据库配置
    static QString sqlHost;             // 数据库主机
    static QString sqlUserName;         // 数据库用户名
    static QString sqlPassword;         // 数据库密码
    static QString sqlDatabase;         // 数据库名
    static int sqlPort;                 // 数据库端口
};
    



#endif // GLOBAL_H