#include "Headers\pwdforgot.h"
#include "ui_pwdforgot.h"

PwdForgot::PwdForgot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwdForgot)
{
    ui->setupUi(this);
}

PwdForgot::~PwdForgot()
{
    delete ui;
}
