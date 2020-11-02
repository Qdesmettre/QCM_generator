#ifndef THANKS_H
#define THANKS_H

#include <QDialog>

namespace Ui {
class Thanks;
}

class Thanks : public QDialog
{
    Q_OBJECT

public:
    explicit Thanks(QWidget *parent = nullptr);
    ~Thanks();
    int exec() override;

public slots:
    void on_close_clicked();

private:
    Ui::Thanks *ui;
};

#endif // THANKS_H
