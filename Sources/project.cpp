#include "Headers\project.h"
#include <QTimer>

Project::Project(QWidget *parent) : QScrollArea(parent)
{
    initAttrib();
    initConnect();
}
void Project::initAttrib(){
    m_add = new QPushButton("+");
    m_del = new QPushButton("-");
        m_del->setEnabled(false);
    m_layout = new QGridLayout;
    m_layout->addWidget(m_add, 0,0);
    m_layout->addWidget(m_del, 0, 1);
    m_container = new QWidget;
    m_container->setLayout(m_layout);
    setWidget(m_container);
    setWidgetResizable(true);
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
    m_layout->addWidget(m_add, rows, 0);
    m_layout->addWidget(m_del, rows, 1);
}
void Project::add(){
    m_questions.push_back(new Question(nullptr, "", 4, m_questions.size()+1));

    replace();

    m_del->setEnabled(true);
}
void Project::del(){
    m_layout->removeWidget(m_questions.back());
    delete m_questions.back();
    m_questions.pop_back();
    if(m_questions.size() == 0) m_del->setEnabled(false);
    else replace();
}
