#include "Headers\projectassist.h"
#include "ui_projectassist.h"
#include <QFileDialog>

ProjectAssist::ProjectAssist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectAssist)
{
    ui->setupUi(this);
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
ProjectAssist::~ProjectAssist()
{
    delete ui;
}
