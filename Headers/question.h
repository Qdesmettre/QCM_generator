#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <QLineEdit>
#include <QFormLayout>
#include <QString>
#include <QPushButton>
#include "choice.h"
#include <QScrollArea>

class Question : public QWidget
{
    Q_OBJECT

public:
    Question(QWidget *parent = nullptr, const QString &name = "", const unsigned &choices = 4, const unsigned &index = 1);
    ~Question();
public slots:
    void add();
    void del();

signals:

private:
    void initConnections();

    std::vector<Choice*> m_choices;
    QLabel *m_num;
    QLineEdit *m_name;
    QFormLayout *m_layout;
    QHBoxLayout *m_optLay;
    QPushButton *m_add, *m_del;
    QScrollArea *m_sa;
    QWidget *m_container;
    QVBoxLayout *m_mainLayout;
};

#endif // QUESTION_H
