#ifndef CHOICE_H
#define CHOICE_H

#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>

class Choice
{
public:
    Choice(const QString &name = "", const char &num = 1, const bool &isCorrect = false);
    ~Choice();

    QString name() const;
    unsigned char num() const;
    bool isCorrect() const;
    QHBoxLayout* layout();
private:
    QLineEdit *m_name;
    QLabel *m_num;
    QCheckBox *m_correct;
    QHBoxLayout *m_layout;
};

#endif // CHOICE_H
