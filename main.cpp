#include "widget.h"
#include "appinit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 应用程序初始化
    if (AppInit::getInstance()->init() == false) return 0;

    Widget w;
    w.show();
    return a.exec();
}
