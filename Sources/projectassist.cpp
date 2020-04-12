#include "Headers\projectassist.h"
#include "ui_projectassist.h"

ProjectAssist::ProjectAssist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectAssist)
{
    ui->setupUi(this);
}

ProjectAssist::~ProjectAssist()
{
    delete ui;
}
