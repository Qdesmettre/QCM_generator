#include "Headers\login.h"

LogIn::LogIn(QWidget *parent) : QWidget(parent)
{
    initAtrib();
    initLay();
    initConect();

}
void LogIn::initLay(){

    QHBoxLayout *temp = new QHBoxLayout;
        temp->addWidget(m_logIn);
        temp->addWidget(m_signIn);

    m_lay->addRow(tr("Identifiant :"), m_id);
    m_lay->addRow(tr("Mot de passe :"), m_mdp);

    m_lay->addRow(temp);

    setLayout(m_lay);
}
void LogIn::initAtrib(){
    m_signIn = new QPushButton(tr("Inscription"));
    m_logIn = new QPushButton(tr("Connexion"));
    m_id = new QLineEdit;
    m_mdp = new QLineEdit;
    m_lay = new QFormLayout;
}
void LogIn::initConect(){
    QObject::connect(m_signIn, SIGNAL(clicked()),
                     this, SLOT(signIn()));
    QObject::connect(m_logIn, SIGNAL(clicked()),
                     this, SLOT(logIn()));
}
