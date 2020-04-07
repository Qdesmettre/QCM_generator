#ifndef PWDFORGOT_H
#define PWDFORGOT_H

#include <QDialog>

namespace Ui {
class PwdForgot;
}

class PwdForgot : public QDialog
{
    Q_OBJECT

public:
    explicit PwdForgot(QWidget *parent = nullptr);
    ~PwdForgot();

private:
    Ui::PwdForgot *ui;
};

#endif // PWDFORGOT_H
