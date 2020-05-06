#include "choice.h"

Choice::Choice(const QString &name, const char &num, const bool &isCorrect, QWidget *parent):
    QWidget(parent)
{
    m_delete.setText("x");
    m_name.setText(name);
    m_num.setText(QString(char(96+num))+")");
    m_correct.setChecked(isCorrect);


    m_layout.addWidget(&m_num);
    m_layout.addWidget(&m_name);
    m_layout.addWidget(&m_correct);
    m_layout.addWidget(&m_delete);

    setLayout(&m_layout);
    QObject::connect(&m_delete, SIGNAL(clicked()), this, SLOT(del()));
}
Choice::Choice(const Choice& c)// : QWidget(nullptr)
{
    /*m_delete.setText("x");
    m_name.setText(c.name());
    m_num.setText(c.m_num.text());
    m_correct.setChecked(c.m_correct.isChecked());

    m_layout.addWidget(&m_num);
    m_layout.addWidget(&m_name);
    m_layout.addWidget(&m_correct);
    m_layout.addWidget(&m_delete);

    setLayout(&m_layout);*/
}
void Choice::operator=(const Choice &c){
    /*m_delete.setText("x");
    m_name.setText(c.name());
    m_num.setText(c.m_num.text());
    m_correct.setChecked(c.m_correct.isChecked());

    m_layout.addWidget(&m_num);
    m_layout.addWidget(&m_name);
    m_layout.addWidget(&m_correct);
    m_layout.addWidget(&m_delete);

    setLayout(&m_layout);*/
}
void Choice::setNum(unsigned char const& n){
    m_num.setText(QString(char(96+n))+")");
}
void Choice::del(){
    emit destroyed(m_num.text().toStdString()[0]-97);
    delete this;
}
QString Choice::name() const{return m_name.text();}
unsigned char Choice::num() const{return m_num.text().remove(QString(")")).toUShort();}
bool Choice::isCorrect() const{return m_correct.isChecked();}
Choice::~Choice(){

}
