#ifndef DISCIPLINEMANAGER_H
#define DISCIPLINEMANAGER_H
#include <QList>
#include "discipline.h"

class DisciplineManager
{
public:

    DisciplineManager();
    virtual void getDisList(QList<Discipline*> _disciplines = QList<Discipline*>()) = 0;
    virtual void addDiscipline(int id, QString name) = 0;
    virtual void editDiscipline(int id, QString name) = 0;
    virtual void removeDiscipline(int id) = 0;

};

#endif // DISCIPLINEMANAGER_H
