#ifndef STATEMENT_H
#define STATEMENT_H
#include "discipline.h"
#include <QString>
#include <QDate>

class Statement
{
public:
    Statement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner);

    Discipline *discipline;
    int sem;
    QString type;
    QString group;
    QString number;
    QString date;
    QString date2;
    QString owner;
    int ID;

    ~Statement();
};

#endif // STATEMENT_H
