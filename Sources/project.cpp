#include "Headers\project.h"

Project::Project() :
    QScrollArea()
{
    m_add = new QPushButton("+");
    m_del = new QPushButton("-");
    m_content = new QGridLayout;
    m_container = new QWidget;
    m_questions.push_back(new Question);
    m_content->addWidget(m_questions[0], 0, 0, 2, 1);
    m_content->addWidget(m_add, 1, 0);
    m_content->addWidget(m_del, 1, 1);

    initConnections();
}
void Project::initConnections(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(del()));
}
