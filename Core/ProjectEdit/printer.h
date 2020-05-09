#ifndef PRINTER_H
#define PRINTER_H

#include <QDialog>
#include <QTextEdit>
namespace Ui {
class PrintSetter;
}

class PrintSetter : public QDialog
{
    Q_OBJECT

public:
    explicit PrintSetter(QWidget *parent = nullptr);
    ~PrintSetter();

    QTextEdit *text() const;
    QString preQ() const;
    QString preC() const;
    QString persoQ() const;
    QString persoC() const;
    int fontQ() const;
    int fontC() const;
    int fontSizeQ() const;
    int fontSizeC() const;
    bool letterQ() const;
    bool letterC() const;
    bool boldQ() const;
    bool boldC() const;


public slots:
    int exe();

    void actuBut();
    void on_fontSizeE_currentIndexChanged(int const& i);
    void on_fontE_currentIndexChanged(int const& i);
    void on_boldE_clicked();
    void on_obliqueE_clicked();
    void on_leftToRight_clicked();
    void on_center_clicked();
    void on_rightToLeft_clicked();

    void on_affQues_currentIndexChanged(int const& i);
    void on_boldQ_clicked();
    void on_fontQ_currentIndexChanged(int const& i);
    void on_fontSizeQ_currentIndexChanged(int const& i);

    void on_affC_currentIndexChanged(int const& i);
    void on_boldC_clicked();
    void on_fontC_currentIndexChanged(int const& i);
    void on_fontSizeC_currentIndexChanged(int const& i);

private:
    Ui::PrintSetter *ui;

    bool m_bold, m_oblique;
};

class PrinterInfo{
public:

    PrinterInfo(PrintSetter const& set);

private:
    QString text;
    QString preQ, persoQ,
            preC, persoC;
    int fontSizeQ, fontSizeC,
        fontQ, fontC;
    bool letterQ, boldQ,
         letterC, boldC;


};

#endif // PRINTER_H
