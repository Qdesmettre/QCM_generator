#include "Headers\question.h"

Question::Question(QWidget *parent, const QString &name, const unsigned &choices, const unsigned &index) :
QWidget(parent)
{

    m_layout = new QFormLayout;
        m_num = new QLabel(QString().setNum(index)+"/");
        m_name = new QLineEdit(name);
        m_layout->addRow(m_num, m_name);

    for(unsigned i(0); i<choices; i++){
        m_choices.push_back(Choice("", i+1));
        m_layout->addRow(m_choices[i].layout());
    }

    m_add = new QPushButton("+");
    m_del = new QPushButton("-");
    m_layout->addRow(m_add, m_del);
    setLayout(m_layout);
    initConnections();
}
void Question::initConnections(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(del()));
}
void Question::add(){
    m_choices.push_back(Choice("", m_choices.size()+1));
    m_layout->insertRow(m_layout->count()-2, m_choices[m_choices.size()-1].layout());
}
void Question::del(){
    m_layout->removeRow(m_choices[m_choices.size()-1].layout());
    m_choices.pop_back();
}
