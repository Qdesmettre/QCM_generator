#include "project.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QSpinBox>
#include <iostream>

Project::Project(const QString &empla, const QString &name, QTabWidget *tParent, QWidget *parent) :
    QWidget(parent),
    m_name(name),
    m_parent(tParent),
    m_isSaved(true)
{
    initAttrib();
    initConnect();
    setEmpla(empla);
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
        connect(m_questions[i], SIGNAL(edited()), this, SLOT(projectChanged()));
    }
    replace();
}
QString Project::empla()const{
    return m_empla;
}
QString Project::name() const{
    return m_name;
}
void Project::setEmpla(const QString &n){
    if(n.size() <= 4){
        m_empla = n;
        return;
    }
    if(QFileInfo(n).suffix() == "qcm")
        m_empla = n;
    else if(n.back() != "/" || n.back() != "\\")
        m_empla = n+m_name+".qcm";
    else
        m_empla = n+".qcm";
}
void Project::setName(QString n){
    m_name = n;
}
void Project::initAttrib(){
    m_mainLay = new QVBoxLayout;
    m_optLay = new QHBoxLayout;
    m_sa = new QScrollArea;
    m_add = new QPushButton("Ajouter question");
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

    m_oldTemps = stack<TempProject>();
    m_futureTemps = stack<TempProject>();
    m_current = currentTemp();
}
std::vector<Question*> Project::questions() const{
    return m_questions;
}
void Project::initConnect(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
    connect(m_add, SIGNAL(clicked()), this, SLOT(projectChanged()));
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
        // On ajoute tous les widgets
        for(unsigned i(0); i<m_questions.size(); i++){
            m_layout->addWidget(m_questions[i], i/nb, i%nb);
        }
    }
}
void Project::add(){
    m_questions.push_back(new Question(nullptr, "", 4, m_questions.size()+1));
    connect(m_questions.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    connect(m_questions.back(), SIGNAL(edited()), this, SLOT(nSaved()));
    connect(m_questions.back(), SIGNAL(edited()), this, SLOT(projectChanged()));
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
void Project::exportProject(){
    if(!hasChoices()){
        QMessageBox::warning(parentWidget()->parentWidget(),
                             "Avertissement",
                             "Il est impossible d'exporter votre projet, car certaines questions n'ont pas de choix.\n"
                             "Veuillez utiliser au moins 1 choix par question.");
        return;
    }
    if(!hasOneCorrect()){
        QMessageBox::warning(parentWidget()->parentWidget(),
                             "Avertissement",
                             "Il est impossible d'exporter votre projet, car certaines questions n'ont pas de réponse marquées correcte.\n"
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


    QFileDialog d(parentWidget()->parentWidget(),
                  "Enregistrer",
                  empla().remove(".qcm"),
                  "Document PDF (*.pdf);;Document Word (*.docx);;Document OpenOffice (*.odt);;Fichier texte (*.txt)");
    d.setAcceptMode(QFileDialog::AcceptSave);
    d.setFileMode(QFileDialog::AnyFile);

    if(d.exec() == 0 || d.selectedFiles().size() == 0)
        return;

    QString path = d.selectedFiles().at(0);
    QString filter = d.selectedNameFilter();

    if(path == "" || filter == "")
        return;

    if(filter == "Document PDF (*.pdf)")
        printToPdf(pr, path);
    else if(filter == "Document Word (*.docx)")
        printToDocx(pr, path);
    else if(filter == "Document OpenOffice (*.odt)")
        printToOdt(pr, path);
    else if(filter == "Fichier texte (*.txt)")
        printToTxt(pr, path);
}
void Project::undo(){
    if(m_oldTemps.empty())
        return;

    m_futureTemps.push(m_current);

    load(m_oldTemps.top());
    m_oldTemps.pop();

    m_current = currentTemp();

    nSaved();
}
void Project::redo(){
    if(m_futureTemps.empty())
        return;

    m_oldTemps.push(m_current);

    load(m_futureTemps.top());
    m_futureTemps.pop();

    m_current = currentTemp();

    nSaved();

}
void Project::load(const TempProject &it){
    // Chargement de it
    std::vector<Question*> ques;
    for(int i(0), n(it.questions.size()); i<n; i++){
        std::vector<Choice*> ch;
        for(int j(0), m(it.questions[i].choices.size()); j<m; j++){
            TempChoice temp = it.questions[i].choices[j];
            ch.push_back(new Choice(temp.name, temp.num, temp.correct, nullptr));
        }
        TempQuestion temp = it.questions[i];
        ques.push_back(new Question(nullptr, temp.name, temp.choices.size(), temp.num.toInt()));
    }
    m_empla = it.empla;
    m_name = it.name;
    setQuestions(ques);

    emit nameChanged(m_name);

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
TempProject Project::currentTemp() const{
    std::vector<TempQuestion> tempQuestions;
    for(unsigned i(0), size(m_questions.size()); i<size; i++){
        std::vector<TempChoice> tempChoices;
        for(unsigned j(0), jSize(m_questions[i]->choices().size()); j<jSize; j++){
            Choice c = *m_questions[i]->choices()[j];
            tempChoices.push_back(TempChoice(c.name(),
                                             c.num(),
                                             c.isCorrect()));
        }
        Question q = *m_questions[i];
        tempQuestions.push_back(TempQuestion(q.name(0), q.num(""), tempChoices));
    }
    return TempProject(empla(), name(), tempQuestions);
}
void Project::projectChanged(){
    m_futureTemps = std::stack<TempProject>();
    m_oldTemps.push(m_current);
    m_current = currentTemp();
}
void Project::printToPdf(const PrintSetter& pr, const QString& path){
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
void Project::printToDocx(const PrintSetter &pr, const QString &path){

}
void Project::printToOdt(const PrintSetter& pr, const QString& path){

}
void Project::printToTxt(const PrintSetter& pr, const QString& path){

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
