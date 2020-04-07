#include "Headers\pwdforgot.h"

#include <QVBoxLayout>

PwdForgot::PwdForgot(QWidget *parent) :
    QWizard(parent)
{
    setWindowTitle(tr("Récupération de mot de passe"));
    initAttribute();
    initIdPage();
    initAnsPage();
    initNewPwdPage();
    initConfirmPage();
    initConnections();
}
void PwdForgot::initAttribute(){
    m_idPage = (new QWizardPage);
    m_ansPage = (new QWizardPage);
    m_nwPwPage = (new QWizardPage);
    m_idLab = (new QLabel(tr("Nom d'utilisateur")));
    m_quesLab = (new QLabel);
    m_nwPwdLab = (new QLabel(tr("Nouveau mot de passe")));
    m_confirNwPwLab = new QLabel(tr("Confirmez le mot de passe"));
    m_error = (new QLabel);
    m_idLine = new QLineEdit;
    m_ansLine = new QLineEdit;
    m_pwd1Line = new QLineEdit;
        m_pwd1Line->setEchoMode(QLineEdit::EchoMode::Password);
    m_pwd2Line = new QLineEdit;
        m_pwd2Line->setEchoMode(QLineEdit::EchoMode::Password);
    m_seePw1 = new QPushButton(tr("Voir"));
    m_seePw2 = new QPushButton(tr("Voir"));
    m_confirmPage = new QWizardPage;
    m_confirmChange = new QLabel(tr("Votre mot de passe a bien été modifié.\n\nVeuillez consulter votre boite mail pour avoir confirmation."));
    m_confirmLay = new QGridLayout;
    m_idLay = new QGridLayout;
    m_quesLay = new QGridLayout;
    m_pwdLay = new QGridLayout;
    m_mailLab = new QLabel(tr("Adresse mail"));
    m_mailLine = new QLineEdit;
}
void PwdForgot::initIdPage(){
    m_idLay->addWidget(m_idLab,  0, 0, 1, 2);
    m_idLay->addWidget(m_idLine, 1, 0, 1, 1);
    m_idLay->addWidget(m_mailLab, 2, 0, 1, 2);
    m_idLay->addWidget(m_mailLine, 3, 0, 1, 1);
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
    m_pwdLay->addWidget(m_nwPwdLab, 0, 0, 1, 4);
    m_pwdLay->addWidget(m_pwd1Line, 1, 0, 1, 1);
    m_pwdLay->addWidget(m_seePw1, 1, 1, 1, 1);
    m_pwdLay->addWidget(m_confirNwPwLab, 2, 0, 1, 4);
    m_pwdLay->addWidget(m_pwd2Line, 3, 0, 1, 1);
    m_pwdLay->addWidget(m_seePw2, 3, 1, 1, 1);
    m_nwPwPage->setLayout(m_pwdLay);
    setPage(2, m_nwPwPage);
}
void PwdForgot::initConfirmPage(){
    m_confirmLay->addWidget(m_confirmChange);
    m_confirmPage->setLayout(m_confirmLay);
    setPage(3, m_confirmPage);
}
void PwdForgot::initConnections(){
    QObject::connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(changeIndex(int)));
    QObject::connect(m_seePw1, SIGNAL(pressed()), this, SLOT(setPw1Visible()));
    QObject::connect(m_seePw1, SIGNAL(released()), this, SLOT(setPw1Hidden()));
    QObject::connect(m_seePw2, SIGNAL(pressed()), this, SLOT(setPw2Visible()));
    QObject::connect(m_seePw2, SIGNAL(released()), this, SLOT(setPw2Hidden()));

}

void PwdForgot::setPw1Hidden(){
    m_pwd1Line->setEchoMode(QLineEdit::Password);
}
void PwdForgot::setPw2Hidden(){
    m_pwd2Line->setEchoMode(QLineEdit::Password);
}
void PwdForgot::setPw1Visible(){
    m_pwd1Line->setEchoMode(QLineEdit::Normal);
}
void PwdForgot::setPw2Visible(){
    m_pwd2Line->setEchoMode(QLineEdit::Normal);
}
bool PwdForgot::id_mailOk(){
    return m_idLine->text() == m_mailLine->text();
}
bool PwdForgot::isAnsCorrect(){
    return !m_ansLine->text().isEmpty();
}
QString PwdForgot::persoQuesOf(QString id){
    return "Ou est née votre mère ?";
}
bool PwdForgot::changePwd(QString nw){
    return true;
}
void PwdForgot::changeIndex(int index){
    switch(index){
        case 1:{
            if(!id_mailOk() && m_idLay->count() < 5){
                m_error->setText(tr("Identifiant ou adresse mail incorrecte"));
                // stylesheet de m_error
                m_idLay->addWidget(m_error, 4, 0, 1, 2);
                back();
            }
            else if(id_mailOk()){
                m_idLay->removeWidget(m_error);
                m_quesLab->setText(persoQuesOf(m_idLine->text()));
                button(WizardButton::BackButton)->setEnabled(false);
            }
            else back();
            break;
        }
        case 2:{
            if(!isAnsCorrect() && m_quesLay->count() <3){
                m_error->setText(tr("Réponse incorrecte"));
                // stylesheet de l'erreur
                m_quesLay->addWidget(m_error, 2,0,1,2);
                back();
            }
            else if(isAnsCorrect()){
                m_quesLay->removeWidget(m_error);
                button(WizardButton::BackButton)->setEnabled(false);
            }
            else back();
            break;
        }
        case 3:{
            if(m_pwd1Line->text() != m_pwd2Line->text()){
                m_error->setText(tr("Les mots de passe sont différents"));
                // stylesheet
                if(m_pwdLay->count() < 7)
                    m_pwdLay->addWidget(m_error, 4, 0, 1, 2);
                back();
            }
            else if(m_pwd1Line->text().isEmpty()){
                m_error->setText(tr("Le mot de passe ne peut pas être vide"));
                if(m_pwdLay->count() < 7)
                    m_pwdLay->addWidget(m_error, 4, 0, 1, 2);
                back();
            }
            else if(!changePwd(m_pwd1Line->text())){
                m_error->setText(tr("Impossible de changer le mot de passe. \nVeuillez vérifier votre connexion et réessayer."));
                if(m_pwdLay->count() < 7)
                    m_pwdLay->addWidget(m_error, 4, 0, 1, 2);
                back();
            }
            else{
                m_pwdLay->removeWidget(m_error);
                button(WizardButton::BackButton)->setEnabled(false);
            }
            break;
        }

    }
}
