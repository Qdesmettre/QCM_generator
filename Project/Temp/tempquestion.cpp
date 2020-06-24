#include "tempquestion.h"

TempQuestion::TempQuestion(const QString &name, const QString &num, const std::vector<TempChoice> &choices):
    choices(choices),
    name(name),
    num(num){}

