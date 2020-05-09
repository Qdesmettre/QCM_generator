#include "printer.h"
#include "ui_printer.h"

Printer::Printer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Printer)
{
    ui->setupUi(this);
}

Printer::~Printer()
{
    delete ui;
}
