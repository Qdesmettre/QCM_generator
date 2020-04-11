#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <QLineEdit>
#include <QFormLayout>
#include <QString>
#include <QPushButton>
#include "choice.h"

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
    QPushButton *m_add, *m_del;
};

#endif // QUESTION_H
