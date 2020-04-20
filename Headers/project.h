#ifndef PROJECT_H
#define PROJECT_H

#include <QScrollArea>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "question.h"

class Project : public QWidget
{
    Q_OBJECT
public:
    explicit Project(QWidget *parent = nullptr);
    ~Project();
    std::vector<Question*> questions();

public slots:
    void add();
    void del();
    void replace();
    /*void generate();
    void save();*/

signals:

private:
    void initAttrib();
    void initConnect();

    QVBoxLayout *m_mainLay;
    QHBoxLayout *m_optLay;
    std::vector<Question*> m_questions;
    QPushButton *m_add, *m_del;
    QGridLayout *m_layout;
    QWidget *m_container;
    QScrollArea *m_sa;
};

#endif // PROJECT_H
