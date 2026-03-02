#ifndef STATEMENT_H
#define STATEMENT_H
#include "discipline.h"
#include <QString>
#include <QDate>

class Statement
{
public:
    Statement();
    Discipline *discipline;
    int sem;
    QString type;
    QString group;
    QDate date;
    QString owner;

private:
    int ID;
};

#endif // STATEMENT_H
