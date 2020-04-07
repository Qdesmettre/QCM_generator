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
    m_error = (new QLabel);
    m_idLine = new QLineEdit;
    m_ansLine = new QLineEdit;
    m_pwd1Line = new QLineEdit;
    m_pwd2Line = new QLineEdit;
    m_seePw1 = new QPushButton(tr("Voir"));
    m_seePw2 = new QPushButton(tr("Voir"));
}
