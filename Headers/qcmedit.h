#ifndef QCMEDIT_H
#define QCMEDIT_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>
#include "project.h"
#include <QDragLeaveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
namespace Ui {
class QcmEdit;
}

class QcmEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit QcmEdit(QWidget *parent = nullptr);
    ~QcmEdit() override;
    void open(QString const& empla);
    static std::string from(unsigned beg, unsigned const& end, std::string const& l);

private slots:
    void nouveau();
    void on_actionFermer_triggered();
    void on_actionTout_fermer_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionTout_enregistrer_triggered();
    void on_actionEnregistrer_sous_triggered();
    void on_actionOuvrir_triggered();
    void on_actionQuitter_triggered();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;


private:
    bool save(Project *project);
    void initAttributes();
    static QString nameOf(QString path);

    QTabWidget *m_Gprojects;

    std::vector<Project*> m_projects;

    QLabel *m_wait;
    Ui::QcmEdit *ui;
};

#endif // QCMEDIT_H
