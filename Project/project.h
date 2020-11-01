#ifndef PROJECT_H
#define PROJECT_H

#include <QScrollArea>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "question.h"
#include <QTabWidget>
#include <string>
#include <stack>
#include "../Print/printer.h"
#include "Temp/tempproject.h"
using std::string;
using std::vector;
using std::stack;

class Project : public QWidget
{
    Q_OBJECT
public:
    explicit Project(const QString& empla, const QString& name, QTabWidget *tParent, QWidget *parent = nullptr);
    ~Project();
    std::vector<Question*> questions()const;

    QString empla()const ;
    QString name()const;
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
    void printToPdf();
    void undo();
    void redo();
    void projectChanged();
    /*void generate();
    void save();*/

signals:
    void nameChanged(QString newName);

private:
    void initAttrib();
    void initConnect();

    int maxChoices();
    void load(const TempProject &it);
    TempProject currentTemp() const;

    bool hasOneCorrect() const;
    bool hasChoices() const;

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

    stack<TempProject> m_oldTemps; // La pile utilisée quand on fait ctrl z
    stack<TempProject> m_futureTemps; // La pile utilisée quand on fait ctrl y
    TempProject m_current;

};


#endif // PROJECT_H
