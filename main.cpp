#include "appinit.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 应用程序初始化
    if (AppInit::getInstance()->init() == false) return 0;

    LoginWindow loginWindow;
    loginWindow.show();

    return a.exec();
}
