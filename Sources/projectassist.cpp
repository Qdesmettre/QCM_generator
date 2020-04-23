#include "Headers\projectassist.h"
#include "ui_projectassist.h"
#include <QFileDialog>
#include <dirent.h>


ProjectAssist::ProjectAssist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectAssist)
{

    m_ok = false;
    ui->setupUi(this);
    resize(sizeHint());
    setWindowTitle(tr("Nouveau projet"));
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
void ProjectAssist::on_name_textEdited(QString){
    check();
}
void ProjectAssist::on_folder_textEdited(QString){
    check();
}
void ProjectAssist::check(){
    if(ui->name->text().isEmpty()){
        ui->error->setText(tr("Le nom ne peut pas être vide"));
        ui->ok->setEnabled(false);
        return;
    }
    else if(ui->folder->text().isEmpty()){
        ui->error->setText(tr("L'emplacement de dossier ne peut être vide"));
        ui->ok->setEnabled(false);
        return ;
    }
    else if(!opendir(ui->folder->text().toStdString().c_str())){
        ui->error->setText(tr("Le dossier n'existe pas."));
        ui->ok->setEnabled(false);
        return;
    }
    else{
        QString folder = ui->folder->text();
        if(folder.back() != "/" || folder.back() != "\\") folder.append("/");
        if(QFile::exists(folder+ui->name->text()+".qcm")){
            ui->error->setText(tr("Le projet existe déjà.\nVous pouvez l'ouvrir en fermant cet outil, \npuis en appuyant sur Ctrl+O."));
            ui->ok->setEnabled(false);
            return;
        }

    }
    ui->error->setText("");
    ui->ok->setEnabled(true);

}
void ProjectAssist::on_cancel_clicked(){
    m_ok = false;
}
void ProjectAssist::on_ok_clicked(){
    m_ok = true;
}
bool ProjectAssist::ok() const{
    return m_ok;
}
ProjectAssist::~ProjectAssist()
{
    delete ui;
}
