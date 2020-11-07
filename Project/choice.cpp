#include "choice.h"
#include <iostream>
#include <QApplication>
#include <QDesktopWidget>

QChar number(quint64 n){
    return QChar(char(96+n));
}

QString toBase26(quint64 num){
    QString r;

    quint64 reste(0), quotient(0);

    do{
        quotient = int(num/27);
        reste = num%27;
        r.push_front(number(reste));
        num =quotient;
    }while(num > 0);

    return r;
}


Choice::Choice(const QString &name, const quint64 &num, const bool &isCorrect, QWidget *parent):
    QWidget(parent)
{
    m_delete = new QPushButton(QIcon(":/images/close.png"), "");
    m_name = new QLineEdit(name);

    m_num = new QLabel(toBase26(num)+")");

    m_correct = new QCheckBox;
    m_correct->setChecked(isCorrect);
    m_layout = new QHBoxLayout;


    m_layout->addWidget(m_num);
    m_layout->addWidget(m_name);
    m_layout->addWidget(m_correct);
    m_layout->addWidget(m_delete);

    QObject::connect(m_delete, SIGNAL(clicked()), this, SLOT(del()));
    QObject::connect(m_name, SIGNAL(textChanged(QString)), this, SLOT(changed()));
    QObject::connect(m_correct, SIGNAL(clicked()), this, SLOT(changed()));
}
Choice::Choice(const Choice& c){
    m_delete = new QPushButton(QIcon(":/images/close.png"), "");
    m_name = new QLineEdit(c.m_name->text());
    m_num = new QLabel(c.m_num->text());
    m_correct = new QCheckBox;
    m_correct->setChecked(c.isCorrect());
    m_layout = new QHBoxLayout;

    m_layout->addWidget(m_num);
    m_layout->addWidget(m_name);
    m_layout->addWidget(m_correct);
    m_layout->addWidget(m_delete);


    QObject::connect(m_delete, SIGNAL(clicked()), this, SLOT(del()));
    QObject::connect(m_name, SIGNAL(editingFinished()), this, SLOT(changed()));
}
Choice::Choice(const TempChoice& t){
    m_name->setText(t.name);
    m_num->setText(QString(t.num+96)+")");
    m_correct->setChecked(t.correct);
}
void Choice::operator=(const Choice &c){
    m_name->setText(c.m_name->text());
    m_num->setText(c.m_num->text());
    m_correct->setChecked(c.isCorrect());
}
void Choice::setNum(qulonglong n){
    m_num->setText(QString(char(96+n))+")");
}
void Choice::changed(){emit edited();}
void Choice::del(){
    emit edited();
    emit destroyed(m_num->text().toStdString()[0]-97);
    delete this;
}
QString Choice::name() const{return m_name->text();}
unsigned short Choice::num() const{return m_num->text().remove(QString(")")).toUShort();}
bool Choice::isCorrect() const{return m_correct->isChecked();}
QHBoxLayout* Choice::layout(){return m_layout;}
Choice::~Choice(){
    delete m_delete;
    delete m_name;
    delete m_num;
    delete m_correct;
    delete m_layout;
}
