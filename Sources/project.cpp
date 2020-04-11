#include "Headers\project.h"
#include <iostream>

Project::Project(QWidget *parent) : QScrollArea(parent)
{
    initAttrib();
    initConnect();
    setFixedSize(minimumSize());
}
void Project::initAttrib(){
    m_add = new QPushButton("+");
    m_del = new QPushButton("-");
        m_del->setEnabled(false);
    m_layout = new QFormLayout;
        m_layout->addRow(m_add, m_del);
    m_container = new QWidget;
    setLayout(m_layout);
}
void Project::initConnect(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(del()));
}
void Project::add(){
    m_questions.push_back(new Question(nullptr, "", 4, m_questions.size()+1));
    m_layout->removeWidget(m_add);
    m_layout->removeWidget(m_del);
    m_layout->addRow(m_questions.back());
    m_layout->addRow(m_add, m_del);
    m_del->setEnabled(true);
}
void Project::del(){ // modifier height
    int height = m_questions.back()->size().height();
    m_layout->removeWidget(m_questions.back());
    delete m_questions.back();
    m_questions.pop_back();
    if(m_questions.size() == 0) m_del->setEnabled(false);

    this->resize(size().width()+1, size().height()+1);
    std::cout << m_layout->sizeHint().height() << "  " << this->minimumSize().height() << "\n";
}
