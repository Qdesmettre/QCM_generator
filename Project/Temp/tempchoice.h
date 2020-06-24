#ifndef TEMPCHOICE_H
#define TEMPCHOICE_H

#include <QString>
class TempChoice
{
public:
    TempChoice(const QString& name, const char& num, const bool& correct);
    TempChoice(const TempChoice& t){name = t.name; num = t.num; correct=t.correct;}
    QString name;
    char num;
    bool correct;
};

#endif // TEMPCHOICE_H
