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
bool SignIn::idDispo(QString text){
    return true;
}
bool SignIn::mailDispo(QString text){
    return true;
}
bool SignIn::allOk(){
    if(!ui->idLine->text().isEmpty() && idDispo(ui->idLine->text()) &&
            !ui->mailLine->text().isEmpty() && mailDispo(ui->mailLine->text()) &&
            !ui->pwd1Line->text().isEmpty() && !ui->pwd2Line->text().isEmpty() &&
            (ui->pwd1Line->text() == ui->pwd2Line->text()) &&
            ui->choQSecu->itemText(ui->choQSecu->currentIndex()) != tr("<Question>") &&
            !ui->ansQSecu->text().isEmpty()){
        return true;
    }
    else return false;
}
void SignIn::on_idLine_textEdited(QString text){
    if(!idDispo(text)) ui->error->setText(tr("L'identifiant est déjà pris."));
    else if(allOk()) ui->confirm->setEnabled(true);
    else ui->confirm->setEnabled(false);
}
void SignIn::on_mailLine_textEdited(QString text){
    if(!mailDispo(text) && ui->error->text().isEmpty()) ui->error->setText(tr("L'adresse mail est déjà prise."));
    else if(allOk() && ui->error->text().isEmpty()) ui->confirm->setEnabled(true);
    else ui->confirm->setEnabled(false);
}


SignIn::~SignIn()
{
    delete ui;
}
