#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

public slots:
    void on_confirm_clicked();
    void on_cancel_clicked();
    void on_idLine_textEdited(QString);
    void on_mailLine_textEdited(QString);
    void on_pwd2Line_textEdited(QString);
    void on_pwd1Line_textEdited(QString);
    void on_ansQSecu_textEdited(QString);


private:
    void checkAll();
    bool idDispo(QString text);
    bool mailDispo(QString text);
    bool allOk();
    void registering();

    Ui::SignIn *ui;
};

#endif // SIGNIN_H
