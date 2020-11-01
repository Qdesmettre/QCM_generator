#ifndef PRINTER_H
#define PRINTER_H

#include <QDialog>
#include <QTextEdit>
#include "../Project/question.h"
#include "ToPdf/pdf.h"
namespace Ui {
class PrintSetter;
}

class PrintSetter : public QDialog
{
    Q_OBJECT

public:
    explicit PrintSetter(QWidget *parent = nullptr);
    explicit PrintSetter(const PrintSetter &prtStr);

    QTextEdit *text() const;
    QString preQ() const;
    QString preC() const;
    QString persoQ() const;
    QString persoC() const;
    PDF::Font fontQ() const;
    PDF::Font fontC() const;
    int fontSizeQ() const;
    int fontSizeC() const;
    bool letterQ() const;
    bool letterC() const;
    bool boldQ() const;
    bool boldC() const;
    int nbQues() const;
    int nbChoice() const;

    bool randQues() const;
    bool randChoices() const;

    void setNbQues(int const& n);
    void setNbChoice(int const& n);

    void setMaxQ(int const &n);
    void setMaxC(int const& n);


public slots:

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

class Print{
public:
    Print(const PrintSetter &prtStr,
          const vector<Question*> &questions, const QString &path);
    ~Print(){}

    bool printToPdf();
    static string toString(const QString &q);

private:

    void writeHead();
    void writeBody();
    void writeBottom();
    QString getIntitQ(const Question &ques);
    QString getIntitC(const quint8 i, const quint8 j, const Choice& c);


    void addText(QString const& t, const uchar &fontSize);
    void addWord(const std::string &word, const uchar &fontSize);
    vector<string> wordsOf(string const& str);
    void addLine();

    vector<Question*> chooseQuestions();
    vector<Choice*> chooseChoices(const Question *q, const uchar &n, const bool &random);
    vector<Question*> sortQuestions(uchar const& number, const bool &rand);


    int addCountY(vector<std::string> intit, int fontSize);


    PDF m_pdf;
    const PrintSetter m_printSetter;

    quint16 m_xTaken, m_yTaken;

    const vector<Question*> m_questions;

    QString m_path;
};

#endif // PRINTER_H
