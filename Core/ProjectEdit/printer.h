#ifndef PRINTER_H
#define PRINTER_H

#include <QDialog>

namespace Ui {
class Printer;
}

class Printer : public QDialog
{
    Q_OBJECT

public:
    explicit Printer(QWidget *parent = nullptr);
    ~Printer();

public slots:
    void on_affQues_currentIndexChanged(int const& i);
    void on_boldQ_clicked();
    void on_fontQ_currentIndexChanged(int const& i);
    void on_fontSizeQ_currentIndexChanged(int const& i);

    void on_affC_currentIndexChanged(int const& i);
    void on_boldC_clicked();
    void on_fontC_currentIndexChanged(int const& i);
    void on_fontSizeC_currentIndexChanged(int const& i);

private:
    Ui::Printer *ui;
};

#endif // PRINTER_H
