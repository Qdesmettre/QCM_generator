#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include "question.h"

class Project
{
public:
    Project();

private:
    std::vector<Question> m_questions;
    QPushButton *m_add, *m_del;

};

#endif // PROJECT_H
