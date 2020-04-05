#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>

class LogIn : public QWidget
{
    Q_OBJECT
public:
    explicit LogIn(QWidget *parent = nullptr);

signals:

private:
    void initConect();
    void initAtrib();
    void initLay();

    QPushButton *m_signIn, *m_logIn;
    QLineEdit *m_id, *m_mdp;
    QFormLayout *m_lay;

};

#endif // LOGIN_H
