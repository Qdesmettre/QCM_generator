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
    explicit Project(QString empla, QString name, QWidget *parent = nullptr);
    ~Project();
    std::vector<Question*> questions();

    QString empla();
    QString name();

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

    QString m_empla, m_name;
};

#endif // PROJECT_H
