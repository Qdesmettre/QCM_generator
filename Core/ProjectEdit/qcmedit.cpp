#include "qcmedit.h"
#include "ui_qcmedit.h"
#include <QVBoxLayout>
#include "projectassist.h"
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QMimeData>
QString QcmEdit::nameOf(QString path){
    QString name;
    while(path.back() != "/" && path.back() != "\\"){
        name.insert(0, path.back());
        path.remove(path.size()-1, 1);
    }
    return name;
}
std::string QcmEdit::from(unsigned beg, unsigned const& end, std::string const& l){
    std::string rtrn = "";
    while(beg < end && beg < l.size()){
        rtrn += l[beg];
        beg++;
    }
    return rtrn;
}
QcmEdit::QcmEdit(const int &argc, QStringList const& list, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QcmEdit)
{
    initAttributes();
    ui->setupUi(this);
    setCentralWidget(m_wait);
    setWindowTitle(tr("Qcm Maker", "This is the name of the application"));
    m_wait->setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);

    QObject::connect(ui->actionNouveau_QCM, SIGNAL(triggered()), this, SLOT(nouveau()));
    m_timer.start();

    m_argc = argc;
    m_argv = list;
}
void QcmEdit::show(){
    QWidget::show();
    for(int i(1); i<m_argv.size(); i++){
        if(QFileInfo(m_argv[i]).suffix() == "qcm")
            open(m_argv[i]);
        else QMessageBox::critical(this, QObject::tr("Erreur"), QObject::tr("Impossible d'ouvrir ")+m_argv[i]);
    }
}
void QcmEdit::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}
void QcmEdit::on_actionImprimer_triggered(){
    if(m_Gprojects->count() == 0)
        return;
    QString pEmpla =  QFileDialog::getSaveFileName(this,
                                                   m_projects[m_Gprojects->currentIndex()]->name(),
                                                   m_projects[m_Gprojects->currentIndex()]->empla(),
                                                   tr("Pdf (*.pdf)"));
    if(!pEmpla.isEmpty())
        m_projects[m_Gprojects->currentIndex()]->printToPdf(pEmpla.toStdString());

}
void QcmEdit::dropEvent(QDropEvent *event){
    if(event->mimeData()->urls().isEmpty() || event->mimeData()->urls().first().toLocalFile().isEmpty())
        return;
    for(int i(0); i<event->mimeData()->urls().size(); i++){
        if(QFileInfo(event->mimeData()->urls()[i].toLocalFile()).suffix() != "qcm"){
            QMessageBox::critical(this, tr("Erreur"), event->mimeData()->urls().first().toLocalFile()+tr(" n'est pas un fichier supporté. \n Ne sont supportés que les fichiers .qcm.", "Just before, the path of the unsuported file is specified"));
        }
        else
            open(event->mimeData()->urls()[i].toLocalFile());
    }

}
void QcmEdit::resizeEvent(QResizeEvent *resize){
    if(m_timer.elapsed() > 500){
        for(unsigned i(0); i<m_projects.size(); i++)
            m_projects[i]->replace();
        m_timer.start();
    }
}
void QcmEdit::closeEvent(QCloseEvent *event){
    on_actionTout_fermer_triggered();
}
void QcmEdit::open(const QString &empla){
    if(empla.isEmpty())
        return;

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
        m_projects.push_back(new Project(empla, Pname, m_Gprojects));
        if(ok) m_projects.back()->setQuestions(questions);

        m_Gprojects->addTab(m_projects.back(), Pname+".qcm");
        if(centralWidget() == m_wait){
            setCentralWidget(m_Gprojects);
        }

        QMessageBox::information(this, tr("Ouverture réussie"), tr("Ouverture du projet ", "Just after, will be the project name")+Pname+tr(" réussie.", "Just before, there's the project name"));
    }
    else QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de l'ouverture de ", "Just after, there's the project path")+empla);
}
void QcmEdit::initAttributes(){

    m_Gprojects = new QTabWidget;
    m_wait = new QLabel(tr("\n Pour commencer un nouveau projet, appuyez sur Ctrl+N  \n Ou pour en ouvrir un, appuyez sur Ctrl+O.", "This is the home message"));
}
void QcmEdit::nouveau(){
    m_projects.push_back(new Project("", "", m_Gprojects));
    m_Gprojects->addTab(m_projects.back(), "new.qcm");
    if(centralWidget() == m_wait) setCentralWidget(m_Gprojects);

}
void QcmEdit::on_actionFermer_triggered(){
    if(m_Gprojects->count() == 0 || m_projects.size() == 0)
        return;
    closeProject(unsigned(m_Gprojects->currentIndex()));
}
void QcmEdit::on_actionTout_fermer_triggered(){
    while(m_projects.size() != 0){
        closeProject(m_Gprojects->currentIndex());
    }
}
void QcmEdit::on_actionEnregistrer_triggered(){
    if(m_Gprojects->count() == 0)
        return;

    int i= m_Gprojects->currentIndex();
    if(m_projects[i]->empla().isEmpty())
        on_actionEnregistrer_sous_triggered();
    else{
        if(save(m_projects[i])){
            QString done(tr("Enregistrement du projet ", "There is the project name just after"));
            done.append(m_projects.at(m_Gprojects->currentIndex())->name()+tr(" réussi"));
            QMessageBox::information(this, tr("Enregistrement terminé"), done);
        }
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
    QString file = QFileDialog::getOpenFileName(this, QString(), QString(), tr("Qcm (*.qcm)"));
    if(!file.isEmpty())
        open(file);
}
void QcmEdit::on_actionQuitter_triggered(){
    on_actionTout_fermer_triggered();
    qApp->quit();
}
void QcmEdit::closeProject(const unsigned &index){
    if(!m_projects[index]->isSaved()){
        QMessageBox::StandardButtons choice =
                QMessageBox::question(this, tr("Projet non sauvegardé"),
                                            tr("Voulez vous abandonner les modifications non enregistrées ?"),
                                            QMessageBox::No | QMessageBox::Yes | QMessageBox::Cancel);
        if(choice == QMessageBox::No){
            if(m_projects[index]->empla().isEmpty()){
                on_actionEnregistrer_sous_triggered();
            }
            else{
                save(m_projects[index]);
            }
        }
        else if(choice == QMessageBox::Cancel){
            return;
        }
    }
    m_projects.erase(m_projects.begin()+m_Gprojects->currentIndex());
    m_Gprojects->removeTab(index);
}
bool QcmEdit::save(Project *project){
    std::ofstream saving(project->empla().toStdString().c_str(), std::ios::out | std::ios::binary);
    if(saving.is_open()){
        std::string file = toString(project);
        saving.write(file.c_str(), file.size());
        project->setSaved(true);
        return true;
    }
    else{
        QString error(tr("Erreur lors de l'enregistrement du projet "));
        error.append(project->name()+tr(". Veuillez choisir un autre dossier ou nom puis rééssayez."));
        QMessageBox::critical(this, tr("Enregistrement impossible"), error);
        return false;
    }
}
std::string QcmEdit::toString(Project *project){
    std::string text = "";
    text += "<PjName>";
    QString pjName  = project->name();
    if(QFileInfo(pjName).suffix() == "qcm") pjName.remove(pjName.size()-4, 4);
    text += Project::toString(project->name());
    text += "<!PjName>\n";
    for(unsigned i(0); i<project->questions().size(); i++){
        text += "<ques>";
        text += Project::toString(project->questions()[i]->name(0)) + '\n';
        for(unsigned j(0); j<project->questions()[i]->choices().size(); j++){
            text += "<ans, ok=";
            if(project->questions()[i]->choices()[j]->isCorrect()) text += ("True>");
            else text += ("Fals>");
            text += Project::toString(project->questions()[i]->choices()[j]->name());
            text += "<!ans>\n";
        }
        text += "<!ques>\n";
    }
    return text;
}
QcmEdit::~QcmEdit()
{
    delete ui;
    while(m_projects.size() != 0){
        delete m_projects.back();
        m_projects.pop_back();
    }
    delete m_Gprojects;
}
