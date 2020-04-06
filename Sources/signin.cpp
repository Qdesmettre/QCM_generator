#include "Headers\signin.h"
#include "ui_signin.h"

#include <QMessageBox>

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
}
void SignIn::on_cancel_clicked(){
    QMessageBox::StandardButton choice =
            QMessageBox::question(this, tr("Annuler"), tr("Etes vous sûr ed vouloir annuler votre inscription ?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if(choice == QMessageBox::Yes)
        close();
}
SignIn::~SignIn()
{
    delete ui;
}
