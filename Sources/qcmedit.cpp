#include "Headers\qcmedit.h"
#include "ui_qcmedit.h"
#include <QVBoxLayout>
#include "Headers/projectassist.h"
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
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
    if(a.ok()){
        m_projects.push_back(new Project(a.empla(), a.name()));
        m_Gprojects->addTab(m_projects.back(), a.name());

        save(m_projects.back());

        if(centralWidget() == m_wait) setCentralWidget(m_Gprojects);
    }


}
void QcmEdit::on_actionFermer_triggered(){
    std::vector<Project*>::iterator it(m_projects.begin());
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
void QcmEdit::on_actionEnregistrer_triggered(){
    if(m_Gprojects->count() > 0 && save(m_projects.at(m_Gprojects->currentIndex()))){
        QString done(tr("Enregistrement du projet "));
        done.append(m_projects.at(m_Gprojects->currentIndex())->name()+tr(" réussi"));
        QMessageBox::information(this, tr("Enregistrement terminé"), done);
    }


}
void QcmEdit::on_actionEnregistrer_sous_triggered(){
    if(m_Gprojects->count() != 0){
        m_projects[m_Gprojects->currentIndex()]->setEmpla(QFileDialog::getSaveFileName(this, m_projects[m_Gprojects->currentIndex()]->name(), m_projects[m_Gprojects->currentIndex()]->empla(), tr("Fichier .qcm (*.qcm)")));
        on_actionEnregistrer_triggered();
    }
}
void QcmEdit::on_actionTout_enregistrer_triggered(){
    bool ok = true;
    for(unsigned i(0); i<m_Gprojects->count(); i++){
        if(!save(m_projects.at(i))) ok = false;
    }
    if(m_Gprojects->count() != 0 && ok) QMessageBox::information(this, tr("Enregistrements terminés"), tr("Tous les projets ont bien été enregistrés."));
}
bool QcmEdit::save(Project *project){
    QString empla(project->empla());
    if(empla.back() != "/"|| empla.back() != "\\")
        empla.append("/");
    empla.append(project->name()+".qcm");
    std::ofstream saving(empla.toStdString().c_str(), std::ios::out | std::ios::binary);
    if(saving.is_open()){        
        saving.write("<PjName>", 8);
        saving.write(project->name().toStdString().c_str(), project->name().size());
        saving.write("<!PjName>", 9);
        for(unsigned i(0); i<project->questions().size(); i++){
            saving.write("<ques>", 6);
            saving.write(project->questions()[i]->name().c_str(), project->questions()[i]->name().size());
            for(unsigned j(0); j<project->questions()[i]->choices().size(); j++){
                saving.write("<ans, ok=", 9);
                if(project->questions()[i]->choices()[j]->isCorrect()) saving.write("True>", 5);
                else saving.write("False>", 6);
                saving.write(project->questions()[i]->choices()[j]->name().toStdString().c_str(), project->questions()[i]->choices()[j]->name().size());
                saving.write("<!ans>", 6);
            }
            saving.write("<!ques>", 7);
        }
    }
    else{
        QString error(tr("Erreur lors de l'enregistrement du projet "));
        error.append(project->name()+tr(". Veuillez choisir un autre dossier ou nom puis rééssayez."));
        QMessageBox::critical(this, tr("Enregistrement impossible"), error);
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
