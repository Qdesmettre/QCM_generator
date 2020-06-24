#ifndef CHOICE_H
#define CHOICE_H

#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include "Temp/tempchoice.h"
class Choice : public QWidget
{
    Q_OBJECT
public:
    Choice(const QString &name = "", const char &num = 1, const bool &isCorrect = false, QWidget *parent = nullptr);
    Choice(const Choice& c);
    Choice(const TempChoice& t);
    ~Choice();

    QString name() const;
    unsigned char num() const;
    bool isCorrect() const;
    QHBoxLayout* layout();

    void setNum(unsigned char n);

    void operator=(const Choice& c);

public slots:
    void del();

private slots:
    void changed();

signals:
    void destroyed(int const& index);
    void edited();

private:
    QPushButton *m_delete;
    QLineEdit *m_name;
    QLabel *m_num;
    QCheckBox *m_correct;
    QHBoxLayout *m_layout;
};

#endif // CHOICE_H
