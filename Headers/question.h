#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <QLineEdit>
#include <QFormLayout>
#include <QString>
#include <QPushButton>

class Question
{
public:
    Question(const QString &name = "", const unsigned &choices = 4, const unsigned &index = 1);

private:

    std::vector<QLineEdit*> m_choices;
    QLineEdit *m_name;
    QFormLayout *m_layout;
    QPushButton *m_add, *m_del;
};

#endif // QUESTION_H
