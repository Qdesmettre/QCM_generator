#include "Headers\qcmedit.h"
#include "ui_qcmedit.h"
#include <QVBoxLayout>
#include "Headers/projectassist.h"
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
    m_Gprojects = new QTabWidget;
    m_wait = new QLabel(tr("\n Pour commencer un nouveau projet, appuyez sur Ctrl+N  \n Ou pour en ouvrir un, appuyez sur Ctrl+O."));
}
void QcmEdit::nouveau(){
    ProjectAssist a;
    a.exec();

    m_projects.push_back(new Project);
    m_Gprojects->addTab(m_projects.back(), "a.name()");

    for(int i(0); i<a.nQuestions(); i++){
        m_projects.back()->add(a.nQuestions(), a.nChoices());
        /*while(m_projects.back()->questions().back()->choices()->size() < a.nChoices()){
            m_projects.back()->questions().back()->add();
        }
        while(m_projects.back()->questions().back()->choices()->size() > a.nChoices()){
            m_projects.back()->questions().back()->del();
        }*/

    }
    if(centralWidget() == m_wait) setCentralWidget(m_Gprojects);
}
void QcmEdit::on_actionFermer_triggered(){
    std::vector<Project*>::iterator it;
    it = m_projects.begin();
    for(int i(0); i<m_Gprojects->currentIndex(); i++){
        it++;
    }
    m_projects.erase(it);

    m_Gprojects->removeTab(m_Gprojects->currentIndex());
}
void QcmEdit::on_actionTout_fermer_triggered(){
    while(m_projects.size() != 0){
        m_Gprojects->removeTab(0);
        m_projects.erase(m_projects.begin());
    }
}
QcmEdit::~QcmEdit()
{
    delete ui;    
    delete m_Gprojects;
    for(int i(0); i<m_projects.size(); i++){
        delete m_projects.back();
        m_projects.pop_back();
    }
    delete m_wait;
}
