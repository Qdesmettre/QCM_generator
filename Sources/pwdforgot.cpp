#include "Headers\pwdforgot.h"

#include <QVBoxLayout>

PwdForgot::PwdForgot(QWidget *parent) :
    QWizard(parent)
{
    setWindowTitle(tr("Récupération de mot de passe"));
}
void PwdForgot::initAttribute(){
    m_idPage = (new QWizardPage);
    m_ansPage = (new QWizardPage);
    m_nwPwPage = (new QWizardPage);
    m_idLab = (new QLabel(tr("Nom d'utilisateur ou adresse mail")));
    m_quesLab = (new QLabel);
    m_nwPwdLab = (new QLabel(tr("Nouveau mot de passe")));
    m_confirNwPwLab = new QLabel(tr("Confirmez le mot de passe"));
    m_error = (new QLabel);
    m_idLine = new QLineEdit;
    m_ansLine = new QLineEdit;
    m_pwd1Line = new QLineEdit;
    m_pwd2Line = new QLineEdit;
    m_seePw1 = new QPushButton(tr("Voir"));
    m_seePw2 = new QPushButton(tr("Voir"));
}
void PwdForgot::initIdPage(){
    m_idLay->addWidget(m_idLab,  0, 0, 1, 2);
    m_idLay->addWidget(m_idLine, 1, 0, 1, 1);
    m_idPage->setLayout(m_idLay);
    setPage(0, m_idPage);
}
void PwdForgot::initAnsPage(){
    m_quesLay->addWidget(m_quesLab, 0, 0, 1, 2);
    m_quesLay->addWidget(m_ansLine, 1, 0, 1, 1);
    m_ansPage->setLayout(m_quesLay);
    setPage(1, m_ansPage);
}
void PwdForgot::initNewPwdPage(){
    m_pwdLay->addWidget(m_nwPwdLab, 0, 0, 1, 2);
    m_pwdLay->addWidget(m_pwd1Line, 1, 0, 1, 1);
    m_pwdLay->addWidget(m_confirNwPwLab, 2, 0, 1, 2);
    m_pwdLay->addWidget(m_pwd2Line, 3, 0, 1, 1);
    m_nwPwPage->setLayout(m_pwdLay);
    setPage(2, m_nwPwPage);
}
