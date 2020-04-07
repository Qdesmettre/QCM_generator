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
    // if index = 1: check if index (0) is correct : if the id/email exists
    //                                              if its ok, load the next page normally with the personnal question

private:
    void initAttribute();
    void initIdPage();
    void initAnsPage();
    void initNewPwdPage();

    QWizardPage *m_idPage, *m_ansPage, *m_nwPwPage;
    QLabel *m_idLab, *m_quesLab, *m_nwPwdLab, *m_confirNwPwLab, *m_error;
    QLineEdit *m_idLine, *m_ansLine, *m_pwd1Line, *m_pwd2Line;
    QPushButton *m_seePw1, *m_seePw2;
    QGridLayout *m_idLay, *m_quesLay, *m_pwdLay;

};

#endif // PWDFORGOT_H
