#include "printer.h"
#include "ui_printer.h"

Printer::Printer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Printer)
{
    ui->setupUi(this);
}
void Printer::on_affQues_currentIndexChanged(int const& i){
    ui->persoQues->setEnabled(i == 10);
}
void Printer::on_affC_currentIndexChanged(int const& i){
    ui->persoC->setEnabled(i == 4);
}
void Printer::on_boldC_clicked(){
    if(ui->boldC->isChecked())
        ui->resultC->setText("<strong>Résultat<!strong>");
    else
        ui->resultC->setText("Résultat");
}
void Printer::on_boldQ_clicked(){
    if(ui->boldQ->isChecked())
        ui->resultQ->setText("<strong>Résultat<!strong>");
    else
        ui->resultQ->setText("Résultat");
}
void Printer::on_fontC_currentIndexChanged(int const& i){
    ui->resultC->setFont(QFont(ui->fontC->currentText(), ui->resultC->font().pointSize()));
}
void Printer::on_fontQ_currentIndexChanged(int const& i){
    ui->resultQ->setFont(QFont(ui->fontQ->currentText(), ui->resultQ->font().pointSize()));
}
void Printer::on_fontSizeC_currentIndexChanged(int const& i){
    ui->resultC->setFont(QFont(ui->resultC->font().family(), ui->fontSizeC->currentText().toInt()));
}
void Printer::on_fontSizeQ_currentIndexChanged(int const& i){
    ui->resultQ->setFont(QFont(ui->resultQ->font().family(), ui->fontSizeQ->currentText().toInt()));
}
Printer::~Printer()
{
    delete ui;
}
