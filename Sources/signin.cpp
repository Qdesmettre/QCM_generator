#include "Headers\signin.h"
#include "ui_signin.h"

#include <QMessageBox>

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    setFixedSize(sizeHint());
    setWindowTitle(tr("Inscription"));
}
void SignIn::on_cancel_clicked(){
    QMessageBox::StandardButton choice =
            QMessageBox::question(this, tr("Annuler"), tr("Etes vous sûr de vouloir annuler votre inscription ?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if(choice == QMessageBox::Yes)
        close();
}
void SignIn::checkAll(){
    if(!ui->idLine->text().isEmpty() && !idDispo(ui->idLine->text())){
        ui->error->setText(tr("L'indentifiant n'est pas disponible"));
        ui->confirm->setEnabled(false);
    }
    else if(!ui->mailLine->text().isEmpty() && !mailDispo(ui->mailLine->text())){
        ui->error->setText(tr("L'adresse mail est déjà prise"));
        ui->confirm->setEnabled(false);
    }
    else if((!ui->pwd1Line->text().isEmpty() && !ui->pwd2Line->text().isEmpty()) &&
            ui->pwd1Line->text() != ui->pwd2Line->text()){
        ui->error->setText(tr("Les mots de passe sont différents"));
        ui->confirm->setEnabled(false);
    }
    else if(ui->ansQSecu->text().isEmpty() && ui->choQSecu->currentText() != tr("<Question>")){
        ui->error->setText(tr("La réponse à la question personelle est vide"));
        ui->confirm->setEnabled(false);
    }
    else if(ui->choQSecu->currentText() == tr("<Question>")){
        ui->error->setText("");
        ui->confirm->setEnabled(false);
    }
    else if(ui->idLine->text().isEmpty()){
        ui->error->setText("");
        ui->confirm->setEnabled(false);
    }
    else if(ui->mailLine->text().isEmpty()){
        ui->error->setText("");
        ui->confirm->setEnabled(false);
    }
    else{
        ui->error->setText("");
        ui->confirm->setEnabled(true);
    }
    setFixedSize(sizeHint());
}
bool SignIn::idDispo(QString text){
    return text==ui->mailLine->text();
}
bool SignIn::mailDispo(QString text){
    return text==ui->idLine->text();
}
void SignIn::registering(){
    // Requiring using data base; will be done in  a further update
    QMessageBox::information(this, tr("Inscription réussie"),
    tr("Votre inscription est terminée. \nVeuillez trouver dans votre boite mail un lien pour confirmer votre inscription."));
}
void SignIn::on_idLine_textEdited(QString){
    checkAll();
}
void SignIn::on_mailLine_textEdited(QString){
    checkAll();
}
void SignIn::on_pwd2Line_textEdited(QString){
    checkAll();
}
void SignIn::on_pwd1Line_textEdited(QString){
    checkAll();
}
void SignIn::on_ansQSecu_textEdited(QString){
    checkAll();
}
void SignIn::on_confirm_clicked(){
    registering();
    close();
}

SignIn::~SignIn()
{
    delete ui;
}
