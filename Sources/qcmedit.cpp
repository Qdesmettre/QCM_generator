#include "Headers\qcmedit.h"
#include "ui_qcmedit.h"

QcmEdit::QcmEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QcmEdit)
{
    ui->setupUi(this);
}

QcmEdit::~QcmEdit()
{
    delete ui;
}
