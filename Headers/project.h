#ifndef PROJECT_H
#define PROJECT_H

#include <QScrollArea>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "question.h"

class Project : public QScrollArea
{
    Q_OBJECT
public:
    explicit Project(QWidget *parent = nullptr);

public slots:
    void add();
    void del();
    void replace();

signals:

private:
    void initAttrib();
    void initConnect();

    std::vector<Question*> m_questions;
    QPushButton *m_add, *m_del;
    QGridLayout *m_layout;
    QWidget *m_container;
};

#endif // PROJECT_H
