#include "project.h"
Project::Project(QString empla, QString name, QWidget *parent) : QWidget(parent)
{
    m_name = name;
    // Le chemin complet est spécifié vers un fichier précis
    if((QString(empla[empla.size()-1])+empla[empla.size()-2]+
         empla[empla.size()-3]+empla[empla.size()-4]) == "mcq.") m_empla = empla;
    // Un chemin vers un dossier spécifié, mais sans slash au bout
    else if(empla.back() == "/" ||empla.back() == "\\")
        m_empla = empla+"/";
    // Un chemin vers un dossier bien spécifié
    else m_empla = empla;

    initAttrib();
    initConnect();
}
Project::Project(const Project& p) : QWidget(nullptr)
{
    operator=(p);
}
void Project::operator=(const Project &p){
    m_name = p.m_name;
    // Le chemin complet est spécifié vers un fichier précis
    /*if((QString(p.m_name[p.m_name.size()-1])+p.m_name[p.m_name.size()-2]+
         p.m_name[p.m_name.size()-3]+p.m_name[p.m_name.size()-4]) == "mcq.") m_name = p.m_name;
    // Un chemin vers un dossier spécifié, mais sans slash au bout
    else if(p.m_name.back() == "/" ||p.m_name.back() == "\\")
        m_empla = p.m_name+"/";
    // Un chemin vers un dossier bien spécifié
    else m_empla = p.m_name;*/

    m_questions.clear();
    for(unsigned i(0); i<p.m_questions.size(); i++){
        m_questions.push_back(p.m_questions[i]);
        connect(&m_questions.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    }
    initAttrib();
    initConnect();
}

void Project::setQuestions(const std::vector<Question> &questions){
    m_questions.clear();
    for(unsigned i(0); i<questions.size(); i++){
        m_questions.push_back(questions[i]);
        connect(&m_questions.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    }
    replace();
}
QString Project::empla()const{
    // Le chemin complet est spécifié vers un fichier précis
    if((QString(m_empla[m_empla.size()-1])+m_empla[m_empla.size()-2]+
         m_empla[m_empla.size()-3]+m_empla[m_empla.size()-4]) == "mcq.") return m_empla;
    // Un chemin vers un dossier spécifié, mais sans slash au bout
    else if(m_empla.back() != "/" ||m_empla.back() != "\\")
        return m_empla+"/"+m_name+".qcm";
    // Un chemin vers un dossier bien spécifié
    else return m_empla+".qcm";
}
QString Project::name()const{
    return m_name;
}
void Project::setEmpla(const QString &n){
    m_empla = n;
}
void Project::setName(QString const& n){
    m_name = n;
}
void Project::initAttrib(){
    m_add.setText("+");
    m_optLay.addWidget(&m_add);
    m_optLay.setAlignment(Qt::AlignLeft);
    m_container.setLayout(&m_layout);
    m_sa.setWidget(&m_container);
    m_sa.setWidgetResizable(true);
    m_mainLay.addWidget(&m_sa);
    m_mainLay.addLayout(&m_optLay);
    setLayout(&m_mainLay);
}
std::vector<Question> Project::questions()const{
    return m_questions;
}
void Project::initConnect(){
    QObject::connect(&m_add, SIGNAL(clicked()), this, SLOT(add()));
}
void Project::replace(){
    // On enlève tous les éléments du layout
    for(int i(0); i<m_layout.count(); i++){
        m_layout.removeItem(m_layout.takeAt(i));
    }
    // On calcule le max de widget par ligne
    int nb = m_container.size().width() / m_questions.back().sizeHint().width();
    for(unsigned i(0); i<m_questions.size(); i++){
        m_layout.addWidget(&m_questions[i], i/nb, i%nb);
    }
}
void Project::add(){
    m_questions.push_back(Question(nullptr, "", 4, m_questions.size()+1));
    connect(&m_questions.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    replace();
}
void Project::rename(int const& n){
    std::vector<Question>::iterator it = m_questions.begin();
    for(int i(0); i<n; i++, it++);
    m_questions.erase(it);

    for(unsigned i(0); i<m_questions.size(); i++){
        m_questions[i].setNum(uchar(i+49));
    }
    replace();
}
Project::~Project(){

}

