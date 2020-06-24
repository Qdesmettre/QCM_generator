#ifndef TEMPQUESTION_H
#define TEMPQUESTION_H

#include <vector>
#include "tempchoice.h"
class TempQuestion
{
public:
    TempQuestion(const QString& name, const QString& num, const std::vector<TempChoice>& choices);
    TempQuestion(const TempQuestion& t){choices = t.choices; name = t.name; num = t.num;}
    std::vector<TempChoice> choices;
    QString name, num;

};

#endif // TEMPQUESTION_H
