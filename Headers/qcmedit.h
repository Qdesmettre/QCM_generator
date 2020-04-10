#ifndef QCMEDIT_H
#define QCMEDIT_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>

namespace Ui {
class QcmEdit;
}

class QcmEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit QcmEdit(QWidget *parent = nullptr);
    ~QcmEdit();

public slots:
    void nouveau();

private:
    void initAttributes();

    QTabWidget *m_projects;
    QLabel *m_wait;
    Ui::QcmEdit *ui;
};

#endif // QCMEDIT_H
