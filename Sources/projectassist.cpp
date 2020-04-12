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


ProjectAssist::~ProjectAssist()
{
    delete ui;
}
