#ifndef STATEMENT_H
#define STATEMENT_H
#include "discipline.h"
#include <QString>
#include <QDate>

class Statement
{
public:
    Statement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QDate _date, QDate _date2, QString _owner);

    Discipline *discipline;
    int sem;
    QString type;
    QString group;
    QDate date;
    QDate date2;
    QString owner;

private:
    int ID;
};

#endif // STATEMENT_H
