#ifndef QCMEDIT_H
#define QCMEDIT_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>
#include "project.h"
#include <QDragLeaveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QTime>
#include <QTimer>
namespace Ui {
class QcmEdit;
}

class QcmEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit QcmEdit(int const& argc = 0, QStringList const& list = QStringList(""), QWidget *parent = nullptr);
    ~QcmEdit() override;
    void open(QString const& empla);
    static std::string from(unsigned beg, unsigned const& end, std::string const& l);

public slots:
    void show();

public slots:
    // 1 : quand on veut faire ces actions
    void nouveau();
    void on_actionFermer_triggered();
    void on_actionTout_fermer_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionTout_enregistrer_triggered(bool afficherMessage = true);
    bool on_actionEnregistrer_sous_triggered();
    void on_actionOuvrir_triggered();
    void on_actionQuitter_triggered();
    void on_actionImprimer_triggered();
    void on_actionAnnuler_triggered();
    void on_actionR_tablir_triggered();
    void on_actionA_propos_triggered();
    void on_actionDon_triggered();

    // 2 : les actions qui sont trigger quand on les cochent (pour afficher/ne plus afficher sur la barre d'outils)
    void on_actionNouveau_QCM2_triggered();
    void on_actionFermer_2_triggered();
    void on_actionTout_fermer_2_triggered();
    void on_actionEnregistrer_2_triggered();
    void on_actionTout_enregistrer_2_triggered();
    void on_actionEnregistrer_sous_2_triggered();
    void on_actionOuvrir_2_triggered();
    void on_actionQuitter_2_triggered();
    void on_actionImprimer_2_triggered();
    void on_actionAnnuler_2_triggered();
    void on_actionR_tablir_2_triggered();

    void close(const int& index);
    void checkForNewFiles();
    void changeName(QString newName);
    void setWaitScreen();


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void resizeEvent(QResizeEvent *resize) override;
    void closeEvent(QCloseEvent* event) override;


private:
    bool save(Project *project);
    void closeProject(const unsigned &index);
    std::string toString(Project *project);
    static QString nameOf(QString path);
    std::vector<Project*>::iterator iteratorOf(Project* p);
    void initGprojects();
    void swap(QAction* check, QAction* toAdd, const quint64 index);
    void putAction(QAction* action, const quint64 index);
    void initToolBar();
    void initActions();


    QTabWidget *m_Gprojects;

    std::vector<Project*> m_projects;

    QLabel *m_wait;
    Ui::QcmEdit *ui;

    QTime m_timer;

    int m_argc;
    QStringList m_argv;

    QToolBar* m_toolBar;
};

#endif // QCMEDIT_H
