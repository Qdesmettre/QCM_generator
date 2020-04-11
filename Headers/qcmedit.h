#ifndef QCMEDIT_H
#define QCMEDIT_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>
#include "project.h"

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
    void on_actionFermer_triggered();
    void on_actionTout_fermer_triggered();


private:
    void initAttributes();

    QTabWidget *m_Gprojects;

    std::vector<Project*> m_projects;

    QLabel *m_wait;
    Ui::QcmEdit *ui;
};

#endif // QCMEDIT_H
