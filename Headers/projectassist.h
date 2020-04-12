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

private:
    Ui::ProjectAssist *ui;
};

#endif // PROJECTASSIST_H
