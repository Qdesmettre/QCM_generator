#include "choice.h"

Choice::Choice(const QString &name, const char &num, const bool &isCorrect, QWidget *parent):
    QWidget(parent)
{
    m_delete = new QPushButton("x");
    m_name = new QLineEdit(name);
    m_num = new QLabel(QString(char(96+num))+")");
    m_correct = new QCheckBox;
    m_correct->setChecked(isCorrect);
    m_layout = new QHBoxLayout;


    m_layout->addWidget(m_num);
    m_layout->addWidget(m_name);
    m_layout->addWidget(m_correct);
    m_layout->addWidget(m_delete);

    QObject::connect(m_delete, SIGNAL(clicked()), this, SLOT(del()));
    QObject::connect(m_name, SIGNAL(textEdited(QString)), this, SLOT(changed()));
}
void Choice::setNum(unsigned char n){
    m_num->setText(QString(char(96+n))+")");
}
void Choice::changed(){emit edited();}
void Choice::del(){
    emit edited();
    emit destroyed(m_num->text().toStdString()[0]-97);
    delete this;
}
QString Choice::name() const{return m_name->text();}
unsigned char Choice::num() const{return m_num->text().remove(QString(")")).toUShort();}
bool Choice::isCorrect() const{return m_correct->isChecked();}
QHBoxLayout* Choice::layout(){return m_layout;}
Choice::~Choice(){
    delete m_delete;
    delete m_name;
    delete m_num;
    delete m_correct;
    delete m_layout;
}
