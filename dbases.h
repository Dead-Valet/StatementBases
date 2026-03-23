#ifndef DBASES_H
#define DBASES_H

#include "disciplinemanager.h"
#include "mainwindow.h"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <iostream>

class MainWindow;

class dbases : public DisciplineManager
{
public:
    dbases(MainWindow *win);
    MainWindow *w;
    QSqlDatabase database;
    void getDisList(QList<Discipline*> _disciplines = QList<Discipline*>());
    void addDiscipline(int id, QString name);
    void editDiscipline(int id, QString name);
    void removeDiscipline(int id);
};

#endif // DBASES_H
