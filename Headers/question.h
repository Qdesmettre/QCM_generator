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
    std::vector<Choice*> choices() const;
    std::string name() const;
    void setChoices(std::vector<Choice*> const& choices);
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

    // Mainlayout contient m_sa+m_optLay;
    //      m_optLay contient m_add+m_del
    //      m_sa contient m_container;
    //          m_container contient m_layout
    //              m_layout contient m_num+m_name+m_choices
};

#endif // QUESTION_H
