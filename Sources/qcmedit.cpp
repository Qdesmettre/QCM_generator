#include "Headers\qcmedit.h"
#include "ui_qcmedit.h"
#include <QVBoxLayout>
QcmEdit::QcmEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QcmEdit)
{
    initAttributes();
    ui->setupUi(this);
    setCentralWidget(m_wait);
    m_wait->setAlignment(Qt::AlignCenter);

    QObject::connect(ui->actionNouveau_QCM, SIGNAL(triggered()), this, SLOT(nouveau()));
}
void QcmEdit::initAttributes(){
    m_projects = new QTabWidget;
    m_wait = new QLabel(tr("\n Pour commencer un nouveau projet, appuyez sur Ctrl+N  \n Ou pour en ouvrir un, appuyez sur Ctrl+O."));
}
void QcmEdit::nouveau(){

}
QcmEdit::~QcmEdit()
{
    delete ui;
}
