#include "Headers\project.h"
#include <iostream>

Project::Project(QWidget *parent) : QScrollArea(parent)
{
    initAttrib();
    initConnect();
}
void Project::initAttrib(){
    m_optLay = new QHBoxLayout;
    m_add = new QPushButton("+");
    m_del = new QPushButton("-");
        m_del->setEnabled(false);
    m_optLay->addWidget(m_add);
    m_optLay->addWidget(m_del);
    m_layout = new QGridLayout;
    m_layout->addLayout(m_optLay, 0, 0);
    m_container = new QWidget;
    m_container->setLayout(m_layout);
    setWidget(m_container);
    setWidgetResizable(true);
}
void Project::initConnect(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(del()));
    QObject::connect(this, SIGNAL(resized()), this, SLOT(replace()));
}
void Project::replace(){

}
void Project::add(){
    m_questions.push_back(new Question(nullptr, "", 4, m_questions.size()+1));
    m_layout->removeItem(m_optLay);
    m_layout->addWidget(m_questions.back(), m_layout->count(), 0, 1, 2);
    m_layout->addLayout(m_optLay, m_layout->count(), 0);
    m_del->setEnabled(true);
    m_container->resize(sizeHint());
}
void Project::del(){
    m_layout->removeWidget(m_questions.back());
    delete m_questions.back();
    m_questions.pop_back();
    if(m_questions.size() == 0) m_del->setEnabled(false);
    m_container->resize(m_container->sizeHint());
}
