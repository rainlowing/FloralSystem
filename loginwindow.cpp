#include "loginwindow.h"

// 构造并初始化
LoginWindow::LoginWindow(QWidget *parent) 
    :   QDialog(parent),
        labelUsername(new QLabel("账号：", this)),
        lineEditUsername(new QLineEdit(this)),
        labelPassword(new QLabel("密码：", this)),
        lineEditPassword(new QLineEdit(this)),
        buttonLogin(new QPushButton("登录", this)),
        vBox(new QVBoxLayout(this)),
        hUsername(new QHBoxLayout(this)),
        hPassword(new QHBoxLayout(this)) 
{
    // 控件添加至布局
    hUsername->addWidget(labelUsername);
    hUsername->addWidget(lineEditUsername);

    hPassword->addWidget(labelPassword);
    hPassword->addWidget(lineEditPassword);

    vBox->addLayout(hUsername);
    vBox->addLayout(hPassword);
    vBox->addWidget(buttonLogin);

    // 设置布局
    setLayout(vBox);

}   

// 析构函数
// LoginWindow::~LoginWindow() {
    
// }
