#include "login.h"
#include "ui_login.h"
#include "signin.h"
#include <QMessageBox>
#include "pwdforgot.h"
LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    setWindowTitle(tr("Connexion"));
    setFixedSize(sizeHint());
}
void LogIn::on_signin_clicked(){
    SignIn window;
    window.exec();
}
void LogIn::on_login_clicked(){
    // Load the main window
    QMessageBox::information(this, tr("Réussi"), tr("Connexion réussie"));
    emit connected();
    close();
}
void LogIn::on_pwdForgot_clicked(){
    PwdForgot a;
    a.exec();
}
void LogIn::on_seePwd_pressed(){
    ui->pwdLine->setEchoMode(QLineEdit::Normal);
}
void LogIn::on_seePwd_released(){
    ui->pwdLine->setEchoMode(QLineEdit::Password);
}
LogIn::~LogIn()
{
    delete ui;
}
