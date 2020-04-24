#include "Headers\question.h"

Question::Question(QWidget *parent, const QString &name, const unsigned &choices, const unsigned &index) :
QWidget(parent)
{
    m_sa = new QScrollArea;
    m_container = new QWidget;
    m_sa->setWidget(m_container);
    m_sa->setWidgetResizable(true);
    m_mainLayout = new QVBoxLayout;

    m_layout = new QFormLayout;
        m_num = new QLabel(QString().setNum(index)+"/");
        m_name = new QLineEdit(name);
        m_layout->addRow(m_num, m_name);

    for(unsigned i(0); i<choices; i++){
        m_choices.push_back(new Choice("", i+1));
        m_layout->addRow(m_choices[i]->layout());
    }
    m_container->setLayout(m_layout);

    m_add = new QPushButton(tr("+"));
    m_del = new QPushButton(tr("-"));

    m_optLay = new QHBoxLayout;
    m_optLay->addWidget(m_add);
    m_optLay->addWidget(m_del);
    m_optLay->setAlignment(Qt::AlignLeft);

    m_mainLayout->addWidget(m_sa);
    m_mainLayout->addLayout(m_optLay);

    setLayout(m_mainLayout);

    initConnections();
}
void Question::setChoices(std::vector<Choice *> const& choices){
    while(m_choices.size() != 0){
        delete m_choices.back();
        m_choices.pop_back();
    }
    m_choices = choices;
    for(unsigned i(0); i<m_choices.size(); i++){
        m_layout->addRow(m_choices[i]->layout());
    }
    m_del->setEnabled(true);
}
std::vector<Choice*> Question::choices() const{
    return m_choices;
}
std::string Question::name() const{
    return m_name->text().toStdString();
}
void Question::initConnections(){
    QObject::connect(m_add, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(del()));
}
void Question::add(){
    m_choices.push_back(new Choice("", m_choices.size()+1));
    m_layout->addRow(m_choices.back()->layout());
    m_del->setEnabled(true);
}
void Question::del(){
    m_layout->removeRow(m_choices.back()->layout());
    //delete m_choices.back();
    m_choices.pop_back();
    if(m_choices.size() == 0) m_del->setEnabled(false);
}
Question::~Question(){
    while(m_choices.size() != 0){
        delete m_choices.back();
        m_choices.pop_back();
    }
    delete m_num;
    delete m_name;
    delete m_layout;
    delete m_container;
    delete m_sa;

    delete m_del;
    delete m_add;
    delete m_optLay;

    delete m_mainLayout;
}
