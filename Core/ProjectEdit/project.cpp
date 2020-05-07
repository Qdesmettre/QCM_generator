#include "project.h"
#include <QMessageBox>
#include <sstream>
#include "pdf.h"
#include <QDesktopServices>
#include <QUrl>
std::string Project::toString(const QString &str){
    std::string returned = "";
    for(int i(0); i<str.size(); i++)
        returned += str[i].toLatin1();
    return returned;
}
Project::Project(QString empla, QString name, QTabWidget *tParent, QWidget *parent) : QWidget(parent)
{
    m_name = name;    

    initAttrib();
    initConnect();

    m_isSaved = true;
    m_parent = tParent;

    if(m_empla.size()>4){
        // Le chemin complet est spécifié vers un fichier précis
        if((QString(empla[empla.size()-1])+empla[empla.size()-2]+
             empla[empla.size()-3]+empla[empla.size()-4]) == "mcq.") m_empla = empla;
        // Un chemin vers un dossier spécifié, mais sans slash au bout
        else if(empla.back() == "/" ||empla.back() == "\\")
            m_empla = empla+"/";
        // Un chemin vers un dossier bien spécifié
        else m_empla = empla;
    }
    else m_empla = empla;
}
void Project::setQuestions(const std::vector<Question *> &questions){
    while(m_questions.size() != 0){
        delete m_questions.back();
        m_questions.pop_back();
    }
    m_questions = questions;
    for(unsigned i(0); i<m_questions.size(); i++){
        connect(m_questions[i], SIGNAL(destroyed(int)), this, SLOT(rename(int)));
        connect(m_questions[i], SIGNAL(edited()), this, SLOT(nSaved()));
    }
    replace();
}
QString Project::empla(){
    if(m_empla.size() > 4){
    // Le chemin complet est spécifié vers un fichier précis
    if((QString(m_empla[m_empla.size()-1])+m_empla[m_empla.size()-2]+
         m_empla[m_empla.size()-3]+m_empla[m_empla.size()-4]) == "mcq.") return m_empla;
    // Un chemin vers un dossier spécifié, mais sans slash au bout
    else if(m_empla.back() != "/" ||m_empla.back() != "\\")
        return m_empla+"/"+m_name+".qcm";
    // Un chemin vers un dossier bien spécifié
    else return m_empla+".qcm";
    }
    else return m_empla;
}
QString Project::name(){
    return m_name;
}
void Project::setEmpla(const QString &n){
    m_empla = n;
}
void Project::setName(QString n){
    m_name = n;
}
void Project::initAttrib(){
    m_mainLay = new QVBoxLayout;
    m_optLay = new QHBoxLayout;
    m_sa = new QScrollArea;
    m_add = new QPushButton("+");
    m_optLay->addWidget(m_add);
    m_optLay->setAlignment(Qt::AlignLeft);

    m_layout = new QGridLayout;
    m_container = new QWidget;
    m_container->setLayout(m_layout);
    m_sa->setWidget(m_container);
    m_sa->setWidgetResizable(true);
    m_mainLay->addWidget(m_sa);
    m_mainLay->addLayout(m_optLay);

    setLayout(m_mainLay);
}
std::vector<Question*> Project::questions(){
    return m_questions;
}
void Project::initConnect(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
}
void Project::replace(){
    // On enlève tous les éléments du layout
    for(int i(0); i<m_layout->count(); i++){
        m_layout->removeItem(m_layout->takeAt(i));
    }
    if(m_questions.size() > 0){
    // On calcule le max de widget par ligne
        int nb = m_container->size().width() / m_questions.back()->sizeHint().width();
        if(nb == 0) nb++;
        for(unsigned i(0); i<m_questions.size(); i++){
            m_layout->addWidget(m_questions[i], i/nb, i%nb);
        }
    }
}
void Project::add(){
    m_questions.push_back(new Question(nullptr, "", 4, m_questions.size()+1));
    connect(m_questions.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    connect(m_questions.back(), SIGNAL(edited()), this, SLOT(nSaved()));
    replace();
    nSaved();
}
void Project::rename(int const& n){
    m_questions.erase(m_questions.begin()+n);

    for(unsigned i(0); i<m_questions.size(); i++){
        m_questions[i]->setNum(uchar(i+49));
    }
    replace();
}
void Project::printToPdf(const std::string &empla){
    PDF p;

    p.setFont(PDF::HELVETICA, 12);

    std::vector<string> fText;
    for(unsigned i(0); i<m_questions.size(); i++){
        std::vector<std::string> s;
        QString tText = "";

        // Une ligne par question
        tText += (QString().setNum(i+1))+ + "/ " + m_questions[i]->name(0);
        s = p.wrapText(toString(tText), p.getWidth(), false);
        for(unsigned t(0); t<s.size(); t++){
            fText.push_back(s[t]);
        }
        tText = "";

        for(unsigned j(0); j<m_questions[i]->choices().size(); j++){
            tText += "- " + m_questions[i]->choices()[j]->name();
            s = p.wrapText(toString(tText), p.getWidth()-100, false);
            for(unsigned t(0); t<s.size(); t++){
                fText.push_back(s[t]);
            }
            tText = "";
        }
        fText.push_back("");
    }
    for(unsigned i(0), n(fText.size()); i<n; i++){
        p.showTextXY(fText[i], 50, 745- 20*i);
    }

    std::string errMsg;
    if(p.writeToFile(empla, errMsg))
        if(QMessageBox::question(parentWidget()->parentWidget(), tr("Impression terminée"),
                                 tr("L'impression de votre qcm est terminée.\nDésirez vous l'ouvrir maintenant ?"),
                                 QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes){
            QString path= "";
            for(unsigned i(0); i<empla.size(); i++)
                path += empla[i];
            QDesktopServices::openUrl(QUrl(path));
        }
        else;
    else
        QMessageBox::critical(parentWidget()->parentWidget(), tr("Impression annulée"), tr("Erreur lors de l'impression Pdf de votre qcm.\n Veuillez rééssayer."));

}
void Project::setSaved(const bool &s){
    int i = m_parent->currentIndex();
    if(!s){
        if(m_parent->tabText(i).front() != '*'){
            QString text = m_parent->tabText(i);
            text.push_front('*');
            m_parent->setTabText(i, text);
        }
    }
    else{
        if(m_parent->tabText(i).front() == '*'){
            m_parent->setTabText(i, m_parent->tabText(i).remove(0,1));
        }
    }
    m_isSaved = s;
}
void Project::nSaved(){
    setSaved(false);
}
Project::~Project(){
    while(m_questions.size() != 0){
        delete m_questions.back();
        m_questions.pop_back();
    }
    delete m_layout;
    delete m_container;
    delete m_sa;
    delete m_add;
    delete m_optLay;
    delete m_mainLay;
}

