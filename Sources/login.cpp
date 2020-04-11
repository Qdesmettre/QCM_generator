#include "Headers\login.h"
#include "ui_login.h"
#include "Headers/signin.h"
#include <QMessageBox>
#include "Headers/pwdforgot.h"
#include "Headers/qcmedit.h"
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
    QMessageBox::information(this, "réussi", "connexion réussie");
    QcmEdit *a = new QcmEdit;
    a->show();
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
