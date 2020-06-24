#include "project.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QSpinBox>
#include <iostream>

Project::Project(const QString &empla, const QString &name, QTabWidget *tParent, QWidget *parent) : QWidget(parent)
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

    addTemp();
    m_projIt = m_temp.begin();
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
QString Project::empla()const{
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
QString Project::name() const{
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
    m_add = new QPushButton("Question++");
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
std::vector<Question*> Project::questions() const{
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
void Project::printToPdf(){
    if(!hasChoices()){
        QMessageBox::warning(parentWidget()->parentWidget(),
                             "Avertissement",
                             "Il est impossible d'imprimer en PDF votre projet, car certaines questions n'ont pas de choix.\n"
                             "Veuillez utiliser au moins 1 choix par question.");
        return;
    }
    if(!hasOneCorrect()){
        QMessageBox::warning(parentWidget()->parentWidget(),
                             "Avertissement",
                             "Il est impossible d'imprimer en PDF votre projet, car certaines questions n'ont pas de réponse marquées correcte.\n"
                             "Veuillez marquer au moins une réponse correcte par question.");
        return;
    }
    PrintSetter pr;
    pr.setNbQues(m_questions.size());
    pr.setMaxQ(m_questions.size());

    pr.setNbChoice(maxChoices());
    pr.setMaxC(maxChoices());

    if(pr.exec() == 0)
        return;

    QString path = QFileDialog::getSaveFileName(parentWidget()->parentWidget(),
                                                "Enregistrer",
                                                empla().remove(".qcm"),
                                                "Fichier PDF (*.pdf)");
    if(path == "")
        return;

    Print printer(pr, m_questions, path);
    if(printer.printToPdf()){
        if(QMessageBox::question(parentWidget()->parentWidget(), tr("Impression terminée"),
                                 tr("L'impression de votre qcm est terminée.\nDésirez vous l'ouvrir maintenant ?"),
                                 QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
            QDesktopServices::openUrl(QUrl(path));
        else{}
    }
    else{
        QMessageBox::critical(parentWidget()->parentWidget(), tr("Impression annulée"),
                              tr("Erreur lors de l'impression Pdf de votre qcm.\n Veuillez rééssayer."));
    }
}
void Project::addTemp(){
    std::vector<TempQuestion> tempQuestions;
    for(unsigned i(0), size(m_questions.size()); i<size; i++){
        std::vector<TempChoice> tempChoices;
        for(unsigned j(0), jSize(m_questions[i]->choices().size()); j<jSize; j++){
            tempChoices.push_back(TempChoice(m_questions[i]->choices()[j]->name(),
                                             (m_questions[i]->choices()[j]->num()),
                                             m_questions[i]->choices()[j]->isCorrect()));
        }
        tempQuestions.push_back(TempQuestion(m_questions[i]->name(0), m_questions[i]->num(""), tempChoices));
    }
    m_temp.erase(m_projIt, m_temp.end());
    m_temp.push_back(TempProject(empla(), name(), tempQuestions));
    m_projIt = m_temp.end();
}
void Project::undo(){

    std::cout << "truc" << std::endl;
    if(m_projIt != m_temp.begin()){
        std::cout << "fait" << std::endl;
        m_projIt--;
        load(m_projIt);
    }
}
void Project::redo(){
    if(m_projIt+1 == m_temp.end())
        return;
    m_projIt++;
    load(m_projIt);
}
void Project::load(const vector<TempProject>::iterator &it){
    TempProject temp = *it;
    m_name = temp.name;
    m_empla = temp.empla;


    m_questions.clear();
    for(unsigned i(0), size(temp.questions.size()); i<size; i++){
        vector<Choice*> choices;
        for(unsigned j(0), jSize(temp.questions[i].choices.size()); j<jSize; j++){
            choices.push_back(new Choice(temp.questions[i].choices[j]));
        }
        m_questions.push_back(new Question(nullptr, temp.questions[i].name, 0, temp.questions[i].num.toUInt()));
        m_questions.back()->setChoices(choices);
        connect(m_questions.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
        connect(m_questions.back(), SIGNAL(edited()), this, SLOT(nSaved()));
    }
    replace();
    setSaved(false);
}
int Project::maxChoices(){
    int max = 0;
    for(int i(0); i<m_questions.size(); i++){
        if(m_questions[i]->choices().size() > max)
            max = m_questions[i]->choices().size();
    }
    return max;
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
    addTemp();
    setSaved(false);
}
bool Project::hasOneCorrect() const{
    for(unsigned i(0), size(m_questions.size()); i<size; i++){
        bool hasCorrect = false;
        for(unsigned j(0), sizeC(m_questions[i]->choices().size()); j<sizeC; j++){
            if(m_questions[i]->choices()[j]->isCorrect()){
                hasCorrect = true;
                break;
            }
        }
        if(!hasCorrect)
            return false;
    }
    return true;
}
bool Project::hasChoices() const{
    for(unsigned i(0), sizeQ(m_questions.size()); i<sizeQ; i++){
        if(m_questions[i]->choices().size() == 0)
            return false;
    }
    return true;
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



