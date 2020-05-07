#ifndef PROJECT_H
#define PROJECT_H

#include <QScrollArea>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "question.h"
#include <QTabWidget>
class Project : public QWidget
{
    Q_OBJECT
public:
    explicit Project(QString empla, QString name, QTabWidget *tParent, QWidget *parent = nullptr);
    ~Project();
    std::vector<Question*> questions();

    QString empla();
    QString name();
    bool isSaved()const{return m_isSaved;}

    void setQuestions(std::vector<Question*> const& questions);
    void setEmpla(QString const& n);
    void setName(QString n);
    void setSaved(const bool &s);

    static std::string toString(const QString &str);
public slots:
    void nSaved();
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

    QString m_empla, m_name;

    QVBoxLayout *m_mainLay;
    QHBoxLayout *m_optLay;
    std::vector<Question*> m_questions;
    QPushButton *m_add;
    QGridLayout *m_layout;
    QWidget *m_container;
    QScrollArea *m_sa;
    QTabWidget *m_parent;

    // m_mainLay contient m_sa+m_optLay
    //  m_optLay contient m_add+m_del
    //  m_sa contient m_container
    //      m_container contient m_layout
    //          m_layout contient m_questions
    bool m_isSaved;
};

#endif // PROJECT_H
