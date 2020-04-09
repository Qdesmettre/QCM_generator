#ifndef QCMEDIT_H
#define QCMEDIT_H

#include <QMainWindow>

namespace Ui {
class QcmEdit;
}

class QcmEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit QcmEdit(QWidget *parent = nullptr);
    ~QcmEdit();

private:
    Ui::QcmEdit *ui;
};

#endif // QCMEDIT_H
