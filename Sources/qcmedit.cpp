#include "Headers\qcmedit.h"
#include "ui_qcmedit.h"
#include <QVBoxLayout>
#include "Headers/projectassist.h"
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
QString QcmEdit::nameOf(QString path){
    QString name;
    while(path.back() != "/" && path.back() != "\\"){
        name.insert(0, path.back());
        path.remove(path.size()-1, 1);
    }
    return name;
}
std::string from(unsigned beg, unsigned const& end, std::string const& l){
    std::string rtrn = "";
    while(beg < end && beg < l.size()){
        rtrn += l[beg];
        beg++;
    }
    return rtrn;
}
QcmEdit::QcmEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QcmEdit)
{
    initAttributes();
    ui->setupUi(this);
    setCentralWidget(m_wait);

    setWindowTitle(tr("Qcm Maker"));

    m_wait->setAlignment(Qt::AlignCenter);

    QObject::connect(ui->actionNouveau_QCM, SIGNAL(triggered()), this, SLOT(nouveau()));
}
void QcmEdit::open(const QString &empla){
    std::ifstream open(empla.toStdString().c_str()
                       , std::ios::in | std::ios::binary);
    if(open.is_open()){
        // Le nom du projet
        QString Pname = "";

        // Les questions
        std::vector<Question*> questions;

        std::string ligne;
        unsigned indexQ = 0;
        bool ok = false;

        // On va récupérer le nom du projet ainsi que les questions et leur réponses
        while(getline(open, ligne)){
            switch (ligne[1]) {
            case 'P':
                for(unsigned i(8); ligne[i] != '<' && ligne[i+1] != '!' && ligne[i+2] != 'P'; i++){
                    Pname += ligne[i];
                }
                break;
            // Une nouvelle question est demandée
            case 'q':
                ok= true;
                std::vector<Choice*> choices;
                // On récupère l'intitulé de la question
                QString qname = "";
                for(unsigned i(6); i<ligne.size(); i++){
                    qname += ligne[i];
                }


                // On récupère l'intitulé des choix
                char indexA = 0;
                while(getline(open, ligne) && ligne != "<!ques>"){
                    bool ok = ligne[9]=='T';
                    QString name = "";
                    for(unsigned i(14); from(i, i+6, ligne) != "<!ans>"; i++){
                        name+=ligne[i];
                    }
                    indexA++;
                    choices.push_back(new Choice(name, indexA, ok));
                }

                // Et on rajoute une question au vector :
                indexQ++;
                questions.push_back(new Question(nullptr, qname, choices.size(), indexQ));
                // On attribut les choix trouvés
                questions.back()->setChoices(choices);
                break;
            }
        }
        m_projects.push_back(new Project(empla, Pname));
        std::cout << m_projects.back()->empla().toStdString() << std::endl;
        if(ok) m_projects.back()->setQuestions(questions);

        m_Gprojects->addTab(m_projects.back(), Pname+".qcm");
        if(centralWidget() == m_wait) setCentralWidget(m_Gprojects);
        QMessageBox::information(this, tr("Ouverture réussie"), tr("Ouverture de ")+Pname+tr(" réussie."));
    }
    else QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de l'ouverture de")+empla);
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
        m_Gprojects->addTab(m_projects.back(), a.name()+".qcm");

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
        QString empla = QFileDialog::getSaveFileName(this,
                                                     m_projects[(m_Gprojects->currentIndex())]->name(),
                m_projects[(m_Gprojects->currentIndex())]->empla(), tr("Qcm (*.qcm)"));

        m_projects[m_Gprojects->currentIndex()]->setEmpla(empla);
        m_projects[m_Gprojects->currentIndex()]->setName(nameOf(empla));

        if(save(m_projects.at((m_Gprojects->currentIndex())))){
            m_Gprojects->setTabText(m_Gprojects->currentIndex(), nameOf(m_projects[m_Gprojects->currentIndex()]->empla()));
            QString done(tr("Enregistrement du projet "));
            done.append(m_Gprojects->tabText(m_Gprojects->currentIndex())+tr(" réussi"));
            QMessageBox::information(this, tr("Enregistrement terminé"), done);
        }
    }
}
void QcmEdit::on_actionTout_enregistrer_triggered(){
    bool ok = true;
    for(int i(0); i<m_Gprojects->count(); i++){
        if(!save(m_projects.at((i)))) ok = false;
    }
    if(m_Gprojects->count() != 0 && ok) QMessageBox::information(this, tr("Enregistrements terminés"), tr("Tous les projets ont bien été enregistrés."));
}
void QcmEdit::on_actionOuvrir_triggered(){
    open(QFileDialog::getOpenFileName(this, QString(), QString(), tr("Qcm (*.qcm)")));
}
void QcmEdit::on_actionQuitter_triggered(){
    qApp->quit();
}
bool QcmEdit::save(Project *project){

    std::ofstream saving(project->empla().toStdString().c_str(), std::ios::out | std::ios::binary);
    std::cout << project->empla().toStdString() << std::endl;
    if(saving.is_open()){
        saving.write("<PjName>", 8);
        saving.write(project->name().toStdString().c_str(), project->name().size());
        saving.write("<!PjName>\n", 10);
        for(unsigned i(0); i<project->questions().size(); i++){
            saving.write("<ques>", 6);
            saving.write(project->questions()[i]->name().c_str(), project->questions()[i]->name().size());
            saving.write("\n", 1);
            for(unsigned j(0); j<project->questions()[i]->choices().size(); j++){
                saving.write("<ans, ok=", 9);
                if(project->questions()[i]->choices()[j]->isCorrect()) saving.write("True>", 5);
                else saving.write("Fals>", 5);
                saving.write(project->questions()[i]->choices()[j]->name().toStdString().c_str(),
                             project->questions()[i]->choices()[j]->name().size());
                saving.write("<!ans>\n", 7);
            }
            saving.write("<!ques>\n", 8);
        }        
        return true;
    }
    else{
        QString error(tr("Erreur lors de l'enregistrement du projet "));
        error.append(project->name()+tr(". Veuillez choisir un autre dossier ou nom puis rééssayez."));
        QMessageBox::critical(this, tr("Enregistrement impossible"), error);
        return false;
    }
}
QcmEdit::~QcmEdit()
{
    delete ui;    
    delete m_Gprojects;
    for(unsigned i(0); i<m_projects.size(); i++){
        delete m_projects.back();
        m_projects.pop_back();
    }
    delete m_wait;
}
//195+
