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
    void on_cancel_clicked();
    void on_idLine_textEdited(QString text);
    void on_mailLine_textEdited(QString text);
    void on_pwd2Line_textEdited(QString text);

private:
    bool idDispo(QString text);
    bool mailDispo(QString text);
    bool allOk();

    Ui::SignIn *ui;

    bool m_id;
};

#endif // SIGNIN_H
