#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

class LoginWindow : public QDialog {
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = 0);
    // ~LoginWindow();

public slots:


private:
    // 控件
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QPushButton *buttonLogin;
    // 布局
    QVBoxLayout *vBox;
    QHBoxLayout *hUsername;
    QHBoxLayout *hPassword;
};








#endif // LOGINWINDOW_H 