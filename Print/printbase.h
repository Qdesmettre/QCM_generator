#ifndef PRINTBASE_H
#define PRINTBASE_H

#include <QDialog>
#include "printer.h"

namespace Ui {
class printBase;
}

class printBase : public QDialog
{
    Q_OBJECT

public:
    explicit printBase(PrintSetter *pr, QString* path, QWidget *parent = nullptr);
    ~printBase();

public slots:
    void on_changePath_clicked();
    void on_options_clicked();
    void nameChanged(QString);
    void pathChanged(QString);
    int exec() override;

private:
    Ui::printBase *ui;

    PrintSetter* m_pr;
    QString* m_path;
};

#endif // PRINTBASE_H
