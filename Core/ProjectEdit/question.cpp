#include "question.h"
#include <iostream>
Question::Question(QWidget *parent, const QString &name, const unsigned &choices, const unsigned &index) :
QWidget(parent)
{
    m_sa = new QScrollArea;
    m_container = new QWidget;
    m_sa->setWidget(m_container);
    m_sa->setWidgetResizable(true);
    m_mainLayout = new QVBoxLayout;

    m_layout = new QFormLayout;
        QHBoxLayout *temp = new QHBoxLayout;
        m_delete = new QPushButton("x");
        m_num = new QLabel(QString().setNum(index)+"/");
        m_name = new QLineEdit(name);
        temp->addWidget(m_num);
        temp->addWidget(m_name);
        temp->addWidget(m_delete);
        connect(m_delete, SIGNAL(clicked()), this, SLOT(del()));
        m_layout->addRow(temp);

    for(unsigned i(0); i<choices; i++){
        m_choices.push_back(new Choice("", i+1));
        QObject::connect(m_choices.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
        m_layout->addRow(m_choices[i]->layout());
    }
    m_container->setLayout(m_layout);

    m_add = new QPushButton(tr("+"));

    m_optLay = new QHBoxLayout;
    m_optLay->addWidget(m_add);
    m_optLay->setAlignment(Qt::AlignLeft);

    m_mainLayout->addWidget(m_sa);
    m_mainLayout->addLayout(m_optLay);

    setLayout(m_mainLayout);

    initConnections();
}
void Question::rename(int const& n){
    m_choices.erase(m_choices.begin()+n);
    for(unsigned i(0); i<m_choices.size(); i++){
        m_choices[i]->setNum(uchar(i+1));
    }
}
void Question::setNum(const uchar &n){
    m_num->setText(QString(n)+"/");
}
void Question::setChoices(std::vector<Choice *> const& choices){
    while(m_choices.size() != 0){
        delete m_choices.back();
        m_choices.pop_back();
    }
    m_choices = choices;
    for(unsigned i(0); i<m_choices.size(); i++){
        m_layout->addRow(m_choices[i]->layout());
        connect(m_choices[i], SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    }
}
std::vector<Choice*> Question::choices() const{
    return m_choices;
}
std::string Question::name() const{
    return m_name->text().toStdString();
}
void Question::initConnections(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
}
void Question::add(){
    m_choices.push_back(new Choice("", m_choices.size()+1));
    QObject::connect(m_choices.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    m_layout->addRow(m_choices.back()->layout());
}
void Question::del(){
    emit destroyed(int(m_num->text().toStdString()[0])-49);
    delete this;
}

Question::~Question(){
    while(m_choices.size() != 0){
        delete m_choices.back();
        m_choices.pop_back();
    }
    delete m_num;
    delete m_name;
    delete m_delete;
    delete m_layout;
    delete m_container;
    delete m_sa;
    delete m_add;
    delete m_optLay;

    delete m_mainLayout;
}
