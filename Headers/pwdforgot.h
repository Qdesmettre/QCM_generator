#ifndef PWDFORGOT_H
#define PWDFORGOT_H

#include <QWizard>
#include <QWizardPage>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class PwdForgot : public QWizard
{
    Q_OBJECT

public:
    explicit PwdForgot(QWidget *parent = nullptr);

public slots:
    void changeIndex(int index);
    void setPw1Visible();
    void setPw1Hidden();
    void setPw2Visible();
    void setPw2Hidden();

private:
    bool id_mailOk();
    QString persoQuesOf(QString id);
    bool isAnsCorrect();
    bool changePwd(QString nw);

    void initConnections();
    void initAttribute();
    void initIdPage();
    void initAnsPage();
    void initNewPwdPage();
    void initConfirmPage();

    QWizardPage *m_idPage, *m_ansPage, *m_nwPwPage, *m_confirmPage;
    QLabel *m_idLab, *m_quesLab, *m_nwPwdLab, *m_confirNwPwLab, *m_error, *m_confirmChange;
    QLineEdit *m_idLine, *m_ansLine, *m_pwd1Line, *m_pwd2Line;
    QPushButton *m_seePw1, *m_seePw2;
    QGridLayout *m_idLay, *m_quesLay, *m_pwdLay, *m_confirmLay;

};

#endif // PWDFORGOT_H
