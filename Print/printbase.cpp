#include "printbase.h"
#include "ui_printbase.h"
#include <QFileDialog>

printBase::printBase(PrintSetter *pr, QString *path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::printBase),
    m_pr(nullptr),
    m_path(nullptr)
{
    ui->setupUi(this);
    setFixedSize(440,128);
    m_path = path;
    m_pr = pr;

    setWindowTitle("Exporter");

    ui->format->addItem("Document PDF (*.pdf)");
    ui->format->addItem("Document Word (*.docx)");
    ui->format->addItem("Document OpenOffice (*.odt)");
    ui->format->addItem("Document texte (*.txt)");

    ui->path->setReadOnly(true);
}
int printBase::exec(){
    if(this->QDialog::exec() == 0)
        return 0;

    *m_path = ui->path->text()+"/" + ui->name->text();
    int i = ui->format->currentIndex();
    if(i == 0)
        *m_path += ".pdf";
    else if(i == 1)
        *m_path += ".docx";
    else if(i == 2)
        *m_path += ".odt";
    else if(i == 3)
        *m_path += ".txt";

    return ui->format->currentIndex()+1;
}
void printBase::on_changePath_clicked(){
    QString path = QFileDialog::getExistingDirectory(this, "Sélectionner un emplacement de sauvegarde du fichier");
    if(!path.isEmpty())
        ui->path->setText(path);
}
void printBase::nameChanged(QString text){
    ui->confirm->setDisabled(text.isEmpty() or ui->path->text().isEmpty());
}
void printBase::on_options_clicked(){
    m_pr->exec();
}
void printBase::pathChanged(QString text){
    ui->confirm->setDisabled(text.isEmpty() or ui->name->text().isEmpty());
}

printBase::~printBase()
{
    delete ui;
}
