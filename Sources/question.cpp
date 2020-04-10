#include "Headers\question.h"

Question::Question(const QString &name, const unsigned &choices, const unsigned &index) :
QWidget()
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
