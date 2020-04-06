#include "Headers\login.h"
#include "ui_login.h"
#include "Headers/signin.h"
LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    setWindowTitle(tr("QCM Generator - Connexion"));
    setFixedSize(sizeHint());
}
void LogIn::on_signin_clicked(){
    SignIn *window = new SignIn;
    window->setModal(true);
    window->show();
}
LogIn::~LogIn()
{
    delete ui;
}
