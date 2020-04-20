#include "Headers\projectassist.h"
#include "ui_projectassist.h"
#include <QFileDialog>
#include <dirent.h>


ProjectAssist::ProjectAssist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectAssist)
{
    ui->setupUi(this);
    resize(sizeHint());
}
void ProjectAssist::on_chooseFolder_clicked(){
    ui->folder->setText(QFileDialog::getExistingDirectory(this));
}
QString ProjectAssist::name()const{
    return ui->name->text();
}
QString ProjectAssist::empla() const{
    return ui->folder->text();
}
int ProjectAssist::nChoices() const{
    return ui->nChoices->value();
}
int ProjectAssist::nQuestions() const{
    return ui->nQuestions->value();
}
void ProjectAssist::on_name_textEdited(QString){
    check();
}
void ProjectAssist::on_folder_textEdited(QString){
    check();
}
void ProjectAssist::on_nChoices_valueChanged(int){
    check();
}
void ProjectAssist::on_nQuestions_valueChanged(int){
    check();
}
void ProjectAssist::check(){
    if(ui->name->text().isEmpty()){
        ui->error->setText("Le nom ne peut pas être vide");
        ui->ok->setEnabled(false);
    }
    else if(ui->folder->text().isEmpty()){
        ui->error->setText("L'emplacement de dossier ne peut être vide");
        ui->ok->setEnabled(false);
    }
    else if(!opendir(ui->folder->text().toStdString().c_str())){
        ui->error->setText("Le dossier n'existe pas.");
        ui->ok->setEnabled(false);
    }
    else if(QFile::exists(ui->folder->text()+ui->name->text())){
        ui->error->setText("Le projet existe déjà. Vous pouvez l'ouvrir en fermant cet outil, puis en appuyant sur Ctrl+O.");
        ui->ok->setEnabled(false);
    }
    else{
        ui->error->setText("");
        ui->ok->setEnabled(true);
    }
}
ProjectAssist::~ProjectAssist()
{
    delete ui;
}
