#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include "question.h"
#include <QScrollArea>

class Project : public QScrollArea
{
public:
    Project();

private:
    void initConnections();

    QWidget *m_container;
    std::vector<Question*> m_questions;
    QPushButton *m_add, *m_del;
    QGridLayout *m_content;
};

#endif // PROJECT_H
