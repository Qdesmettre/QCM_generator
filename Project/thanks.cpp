#include "thanks.h"
#include "ui_thanks.h"
#include <QSettings>
Thanks::Thanks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Thanks)
{
    ui->setupUi(this);
    connect(ui->close, SIGNAL(clicked()), this, SLOT(on_close_clicked()));
}
int Thanks::exec(){
    QSettings settings;
    if(settings.value("neverShowAgain").toBool()){
        close();
        return 1;
    }

    return QDialog::exec();
}
void Thanks::on_close_clicked(){
    QSettings settings;
    if(ui->neverShow->isChecked()){
        settings.setValue("neverShowAgain", true);
    }
    else{
        settings.setValue("neverShowAgain", false);
    }
    accept();
}
Thanks::~Thanks()
{
    delete ui;
}
