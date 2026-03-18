#ifndef STATEMENTSMANAGER_H
#define STATEMENTSMANAGER_H
#include "statement.h"
#include <QString>
#include <QDate>

class StatementsManager
{
public:

    StatementsManager();

    virtual void getStatList(QList<Statement*> _statements = QList<Statement*>()) = 0;
    virtual void addStatement(int _ID, QString _discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) = 0;
    virtual void editStatement(int _ID, QString _discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) = 0;
    virtual void removeStatement(int id) = 0;

};

#endif // STATEMENTSMANAGER_H
