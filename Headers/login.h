#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

public slots:
    void on_signin_clicked();
    void on_login_clicked();
    void on_pwdForgot_clicked();


private:

    Ui::LogIn *ui;
};

#endif // LOGIN_H
