#include "Headers\login.h"
#include "ui_login.h"
#include "Headers/signin.h"
#include <QMessageBox>
#include "Headers/pwdforgot.h"
LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    setWindowTitle(tr("Connexion"));
    setFixedSize(sizeHint());
}
void LogIn::on_signin_clicked(){
    SignIn *window = new SignIn;
    window->setModal(true);
    window->show();
}
void LogIn::on_login_clicked(){
    // Load the main window
    QMessageBox::information(this, "réussi", "connexion réussie");
}
void LogIn::on_pwdForgot_clicked(){
    PwdForgot a;
    int b = a.exec();
}
LogIn::~LogIn()
{
    delete ui;
}
