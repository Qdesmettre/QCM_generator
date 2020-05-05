#ifndef PROJECT_H
#define PROJECT_H

#include <QGridLayout>
#include "question.h"

class Project : public QWidget
{
    Q_OBJECT
public:
    explicit Project(QString empla, QString name, QWidget *parent = nullptr);
    Project(const Project& p);
    ~Project() override;
    std::vector<Question> questions() const;

    QString empla()const;
    QString name()const;

    void setQuestions(std::vector<Question> const& questions);
    void setEmpla(QString const& n);
    void setName(QString const& n);

    void operator=(const Project& p);

public slots:
    void add();
    void replace();
    void rename(int const& n);
    /*void generate();
    void save();*/

signals:

private:
    void initAttrib();
    void initConnect();

    QVBoxLayout m_mainLay;
    QHBoxLayout m_optLay;
    std::vector<Question> m_questions;
    QPushButton m_add;
    QGridLayout m_layout;
    QWidget m_container;
    QScrollArea m_sa;

    // m_mainLay contient m_sa+m_optLay
    //  m_optLay contient m_add+m_del
    //  m_sa contient m_container
    //      m_container contient m_layout
    //          m_layout contient m_questions

    QString m_empla, m_name;
};

#endif // PROJECT_H
