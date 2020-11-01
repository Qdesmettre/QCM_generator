#ifndef TEMPPROJECT_H
#define TEMPPROJECT_H

#include "tempquestion.h"
class TempProject
{
public:
    TempProject(const QString& empla, const QString& name, const std::vector<TempQuestion> &questions);
    TempProject(const TempProject& t){empla = t.empla; name = t.name; questions = t.questions;}
    TempProject(){};
    QString empla, name;
    std::vector<TempQuestion> questions;

    void operator=(const TempProject& t){empla = t.empla; name = t.name; questions = t.questions;}

};

#endif // TEMPPROJECT_H
