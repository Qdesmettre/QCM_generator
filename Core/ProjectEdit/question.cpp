#include "question.h"
#include <iostream>
Question::Question(QWidget *parent, const QString &name, const unsigned &choices, const unsigned &index) :
QWidget(parent)
{
    m_sa.setWidget(&m_container);
    m_sa.setWidgetResizable(true);

        QHBoxLayout temp;
        m_delete.setText("x");
        m_num.setText(QString().setNum(index)+"/");
        m_name.setText(name);
        temp.addWidget(&m_num);
        temp.addWidget(&m_name);
        temp.addWidget(&m_delete);
        connect(&m_delete, SIGNAL(clicked()), this, SLOT(del()));
        m_layout.addRow(&temp);

    for(unsigned i(0); i<choices; i++){
        m_choices.push_back(Choice("", i+1));
        QObject::connect(&m_choices.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
        m_layout.addRow(&m_choices[i]);
    }
    m_container.setLayout(&m_layout);

    m_add.setText(tr("+"));

    m_optLay.addWidget(&m_add);
    m_optLay.setAlignment(Qt::AlignLeft);

    m_mainLayout.addWidget(&m_sa);
    m_mainLayout.addLayout(&m_optLay);

    setLayout(&m_mainLayout);

    initConnections();
}
void Question::rename(int const& n){
    std::vector<Choice>::iterator it;
    it = m_choices.begin();
    for(int i(0); i<n; i++){
        it++;
    }
    m_choices.erase(it);

    for(unsigned i(0); i<m_choices.size(); i++){
        m_choices[i].setNum(uchar(i+1));
    }
}
void Question::setNum(const uchar &n){
    m_num.setText(QString(n)+"/");
}
void Question::setChoices(std::vector<Choice> const& choices){
    m_choices.clear();
    for(unsigned i(0); i<choices.size(); i++){
        m_choices.push_back(choices[i]);
        m_layout.addRow(&m_choices.back());
        connect(&m_choices.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    }
}
std::vector<Choice> Question::choices() const{
    return m_choices;
}
std::string Question::name() const{
    return m_name.text().toStdString();
}
void Question::initConnections(){
    QObject::connect(&m_add, SIGNAL(clicked()), this, SLOT(add()));
}
void Question::add(){
    m_choices.push_back(Choice("", m_choices.size()+1));
    QObject::connect(&m_choices.back(), SIGNAL(destroyed(int)), this, SLOT(rename(int)));
    m_layout.addRow(&m_choices.back());
}
void Question::del(){
    emit destroyed(int(m_num.text().toStdString()[0])-49);
    delete this;
}
