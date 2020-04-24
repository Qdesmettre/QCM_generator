#include "Headers\choice.h"

Choice::Choice(const QString &name, const char &num, const bool &isCorrect)
{
    m_name = new QLineEdit(name);
    m_num = new QLabel(QString(char(96+num))+")");
    m_correct = new QCheckBox;
    m_correct->setChecked(isCorrect);
    m_layout = new QHBoxLayout;

    m_layout->addWidget(m_num);
    m_layout->addWidget(m_name);
    m_layout->addWidget(m_correct);
}
QString Choice::name() const{return m_name->text();}
unsigned char Choice::num() const{return m_num->text().remove(QString(")")).toUShort();}
bool Choice::isCorrect() const{return m_correct->isChecked();}
QHBoxLayout* Choice::layout(){return m_layout;}
Choice::~Choice(){
    delete m_name;
    delete m_num;
    delete m_correct;
    delete m_layout;
}
