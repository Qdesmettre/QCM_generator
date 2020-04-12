#ifndef PROJECTASSIST_H
#define PROJECTASSIST_H

#include <QDialog>

namespace Ui {
class ProjectAssist;
}

class ProjectAssist : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectAssist(QWidget *parent = nullptr);
    ~ProjectAssist();
    QString name() const;
    QString empla() const;
    int nChoices() const;
    int nQuestions() const;


public slots:
    void on_chooseFolder_clicked();

signals:
    void finished();

private:
    Ui::ProjectAssist *ui;
};

#endif // PROJECTASSIST_H
