#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <QLabel>
#include <QFormLayout>

class Question
{
public:
    Question();
private:
    std::vector<QLabel*> m_choices;
    QLabel *m_name;
    QFormLayout *m_layout;
};

#endif // QUESTION_H
