// 初始化设置类
#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>

class AppInit : public QObject
{
    Q_OBJECT
public:
    // 公有静态函数，用于获取单例对象
    static AppInit* getInstance();  
    // 构造函数                   
    explicit AppInit(QObject *parent = nullptr);    
    // 应用程序初始化
    bool init();                                   

protected:
    // 目标对象实现事件过滤器，可以拦截应用程序中的所有事件
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    // 私有单例对象
    static AppInit* instance;                     
};

#endif 