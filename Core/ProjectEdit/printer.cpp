#include "printer.h"
#include "ui_printer.h"
PrintSetter::PrintSetter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintSetter)
{
    ui->setupUi(this);
    ui->enTete->setFont(QFont("Courier"));
    m_bold = false;
    m_oblique = false;

    ui->enTete->cursorPositionChanged();

    connect(ui->enTete, SIGNAL(cursorPositionChanged()), this, SLOT(actuBut()));
}
QTextEdit *PrintSetter::text() const{return ui->enTete;}
QString PrintSetter::preC() const{return ui->affC->currentText();}
QString PrintSetter::preQ() const{return ui->affQues->currentText();}
bool PrintSetter::boldC() const{return ui->boldC->isChecked();}
bool PrintSetter::boldQ() const{return ui->boldQ->isChecked();}
QString PrintSetter::persoC() const{return ui->persoC->text();}
QString PrintSetter::persoQ() const{return ui->persoQues->text();}
int PrintSetter::fontC() const{return ui->fontC->currentIndex();}
int PrintSetter::fontQ() const{return ui->fontQ->currentIndex();}
int PrintSetter::fontSizeC() const{return ui->fontSizeC->currentText().toInt();}
int PrintSetter::fontSizeQ() const{return ui->fontSizeQ->currentText().toInt();}

int PrintSetter::exe(){

}
void PrintSetter::actuBut(){
    switch(ui->enTete->currentFont().pointSize()){
    case 6: ui->fontSizeE->setCurrentIndex(0); break;
    case 7: ui->fontSizeE->setCurrentIndex(1); break;
    case 8:ui->fontSizeE->setCurrentIndex(2); break;
    case 9:ui->fontSizeE->setCurrentIndex(3); break;
    case 10:ui->fontSizeE->setCurrentIndex(4); break;
    case 11:ui->fontSizeE->setCurrentIndex(5); break;
    case 12:ui->fontSizeE->setCurrentIndex(6); break;
    case 14:ui->fontSizeE->setCurrentIndex(7); break;
    case 16:ui->fontSizeE->setCurrentIndex(8); break;
    case 18:ui->fontSizeE->setCurrentIndex(9); break;
    case 20:ui->fontSizeE->setCurrentIndex(10); break;
    case 22:ui->fontSizeE->setCurrentIndex(11); break;
    case 24:ui->fontSizeE->setCurrentIndex(12); break;
    case 26:ui->fontSizeE->setCurrentIndex(13); break;
    case 28:ui->fontSizeE->setCurrentIndex(14); break;
    case 36:ui->fontSizeE->setCurrentIndex(15); break;
    case 48:ui->fontSizeE->setCurrentIndex(16); break;
    case 72:ui->fontSizeE->setCurrentIndex(17); break;
    }
    if(ui->enTete->fontFamily() == "Courier")
        ui->fontE->setCurrentIndex(0);
    else if(ui->enTete->fontFamily() == "Helvetica")
        ui->fontE->setCurrentIndex(1);
    else ui->fontE->setCurrentIndex(2);
    QFont tests(ui->boldE->font());
    tests.setBold(ui->enTete->currentFont().bold());
    ui->boldE->setFont(tests);

    tests = ui->obliqueE->font();
    tests.setItalic(ui->enTete->currentFont().italic());
    ui->obliqueE->setFont(tests);

    tests = ui->leftToRight->font();
    tests.setBold(ui->enTete->alignment() == Qt::AlignLeft);
    ui->leftToRight->setFont(tests);

    tests = ui->rightToLeft->font();
    tests.setBold(ui->enTete->alignment() == Qt::AlignRight);
    ui->rightToLeft->setFont(tests);

    tests = ui->center->font();
    tests.setBold(ui->enTete->alignment() == Qt::AlignCenter);
    ui->center->setFont(tests);
}
void PrintSetter::on_boldE_clicked(){
    m_bold = !m_bold;

    QFont font(ui->enTete->currentFont());
    font.setBold(m_bold);
    ui->enTete->setCurrentFont(font);


    QFont fontB(ui->boldE->font());
    fontB.setBold(m_bold);
    ui->boldE->setFont(fontB);
}
void PrintSetter::on_fontE_currentIndexChanged(int const& i){
    ui->enTete->setCurrentFont(QFont(ui->fontE->currentText()));
}
void PrintSetter::on_obliqueE_clicked(){
    m_oblique = !m_oblique;

    QFont font(ui->enTete->currentFont());
    font.setItalic(m_oblique);
    ui->enTete->setCurrentFont(font);

    QFont fontB(ui->obliqueE->font());
    fontB.setItalic(m_oblique);
    ui->obliqueE->setFont(fontB);
}
void PrintSetter::on_fontSizeE_currentIndexChanged(int const& i){
    QFont font(ui->enTete->currentFont().family(), ui->enTete->currentFont().pointSize());
    font.setPointSize(ui->fontSizeE->currentText().toInt());
    ui->enTete->setCurrentFont(font);
}
void PrintSetter::on_leftToRight_clicked(){
    ui->enTete->setAlignment(Qt::AlignLeft);
    QFont font(ui->leftToRight->font());

    ui->center->setFont(font);
    ui->rightToLeft->setFont(font);

    font.setBold(true);
    ui->leftToRight->setFont(font);
}
void PrintSetter::on_rightToLeft_clicked(){
    ui->enTete->setAlignment(Qt::AlignRight);

    QFont font(ui->rightToLeft->font());

    ui->center->setFont(font);
    ui->leftToRight->setFont(font);

    font.setBold(true);
    ui->rightToLeft->setFont(font);
}
void PrintSetter::on_center_clicked(){
    ui->enTete->setAlignment(Qt::AlignCenter);

    QFont font(ui->center->font());

    ui->rightToLeft->setFont(font);
    ui->leftToRight->setFont(font);

    font.setBold(true);
    ui->center->setFont(font);
}

void PrintSetter::on_affQues_currentIndexChanged(int const& i){
    ui->persoQues->setEnabled(i == 9);
}
void PrintSetter::on_boldQ_clicked(){
    if(ui->boldQ->isChecked())
        ui->resultQ->setText("<strong>Résultat<!strong>");
    else
        ui->resultQ->setText("Résultat");
}
void PrintSetter::on_fontQ_currentIndexChanged(int const& i){
    ui->resultQ->setFont(QFont(ui->fontQ->currentText(), ui->resultQ->font().pointSize()));
}
void PrintSetter::on_fontSizeQ_currentIndexChanged(int const& i){
    ui->resultQ->setFont(QFont(ui->resultQ->font().family(), ui->fontSizeQ->currentText().toInt()));
}

void PrintSetter::on_affC_currentIndexChanged(int const& i){
    ui->persoC->setEnabled(i == 3);
}
void PrintSetter::on_boldC_clicked(){
    if(ui->boldC->isChecked())
        ui->resultC->setText("<strong>Résultat<!strong>");
    else
        ui->resultC->setText("Résultat");
}
void PrintSetter::on_fontC_currentIndexChanged(int const& i){
    ui->resultC->setFont(QFont(ui->fontC->currentText(), ui->resultC->font().pointSize()));
}
void PrintSetter::on_fontSizeC_currentIndexChanged(int const& i){
    ui->resultC->setFont(QFont(ui->resultC->font().family(), ui->fontSizeC->currentText().toInt()));
}

PrintSetter::~PrintSetter()
{
    delete ui;
}

PrinterInfo::PrinterInfo(PrintSetter const& set){
    text = set.text()->toHtml();
    preQ = set.preQ();
    preC = set.preC();
    persoQ = set.persoQ();
    persoC = set.persoC();
    fontC = set.fontC();
    fontQ = set.fontQ();
    fontSizeC = set.fontSizeC();
    fontSizeQ = set.fontSizeQ();

}
