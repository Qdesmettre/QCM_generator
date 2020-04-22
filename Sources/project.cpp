#include "Headers\project.h"
#include <QTimer>

Project::Project(QString empla, QString name, QWidget *parent) : QWidget(parent)
{
    m_name = name;
    m_empla = empla;

    initAttrib();
    initConnect();
}
QString Project::empla(){
    return m_empla;
}
QString Project::name(){
    return m_name;
}
void Project::setEmpla(QString n){
    m_empla = n;
}
void Project::initAttrib(){
    m_mainLay = new QVBoxLayout;
    m_optLay = new QHBoxLayout;
    m_sa = new QScrollArea;
    m_add = new QPushButton("+");
    m_del = new QPushButton("-");
        m_del->setEnabled(false);
    m_optLay->addWidget(m_add);
    m_optLay->addWidget(m_del);
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
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(del()));
}
void Project::replace(){
    for(int i(0); i<m_layout->count(); i++){
        m_layout->removeItem(m_layout->takeAt(i));
    }

    int nb = m_container->size().width() / m_questions.back()->sizeHint().width();
    int rows = 0;
    for(unsigned i(0); i<m_questions.size(); i++){
        m_layout->addWidget(m_questions[i], i/nb, i%nb);
        if(i+1 == m_questions.size()) rows = i/nb+1;
    }
}
void Project::add(){
    m_questions.push_back(new Question(nullptr, "", 4, m_questions.size()+1));

    replace();

    m_del->setEnabled(true);
}
void Project::del(){
    //m_layout->removeWidget(m_questions.back());
    delete m_questions.back();
    m_questions.pop_back();
    if(m_questions.size() == 0) m_del->setEnabled(false);
    else replace();
}
Project::~Project(){

    delete m_mainLay;
    delete m_optLay;
    for(unsigned i(0); i<m_questions.size(); i++){
        delete m_questions.back();
        m_questions.pop_back();
    }
    delete m_add;
    delete m_del;
    delete m_layout;
    delete m_container;
    delete m_sa;
}
