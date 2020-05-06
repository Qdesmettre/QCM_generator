#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <QFormLayout>
#include <QString>
#include "choice.h"
#include <QScrollArea>

class Question : public QWidget
{
    Q_OBJECT

public:
    explicit Question(QWidget *parent = nullptr, const QString &name = "", const unsigned &choices = 4, const unsigned &index = 1);
    Question(const Question& q);
    ~Question() override;
    std::vector<Choice> choices() const;
    std::string name() const;
    void setChoices(std::vector<Choice> const& choices);
    void setNum(uchar const& n);

    void operator=(const Question &q);
public slots:
    void add();
    void del();
    void rename(int const& n);

signals:
    void destroyed(int const& n);

private:
    void initConnections();

    QPushButton m_delete;

    std::vector<Choice> m_choices;
    QLabel m_num;
    QLineEdit m_name;

    QFormLayout m_layout;
    QHBoxLayout m_optLay;
    QPushButton m_add;
    QScrollArea m_sa;
    QWidget m_container;
    QVBoxLayout m_mainLayout;

    // Mainlayout contient m_sa+m_optLay;
    //      m_optLay contient m_add
    //      m_sa contient m_container;
    //          m_container contient m_layout
    //              m_layout contient m_num+m_name+m_delete+m_choices
};

#endif // QUESTION_H
