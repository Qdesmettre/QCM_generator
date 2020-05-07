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

    void setQuestions(std::vector<Question*> const& questions);
    void setEmpla(QString const& n);
    void setName(QString n);

public slots:
    void add();
    void replace();
    void rename(int const& n);
    void printToPdf(std::string const& empla);
    /*void generate();
    void save();*/

signals:

private:
    void initAttrib();
    void initConnect();
    static std::string toString(const QString &str);

    QVBoxLayout *m_mainLay;
    QHBoxLayout *m_optLay;
    std::vector<Question*> m_questions;
    QPushButton *m_add;
    QGridLayout *m_layout;
    QWidget *m_container;
    QScrollArea *m_sa;

    // m_mainLay contient m_sa+m_optLay
    //  m_optLay contient m_add+m_del
    //  m_sa contient m_container
    //      m_container contient m_layout
    //          m_layout contient m_questions

    QString m_empla, m_name;
};

#endif // PROJECT_H
