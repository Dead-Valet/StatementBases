#ifndef DBASES_H
#define DBASES_H

#include "disciplinemanager.h"
#include "mainwindow.h"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <iostream>

class MainWindow;

class dbases : public DisciplineManager
{
public:
    dbases(MainWindow *win);
    MainWindow *w;
    QSqlDatabase database;
    int id = 0;
    QString _name;
    QList<Discipline*> disciplines;
    void addDiscipline(int id, QString name);
    void editDiscipline(int id, QString name);
    void removeDiscipline(int id);
    QString line(Discipline *dis);

public slots:
    void getDisList(QList<Discipline*> _disciplines = QList<Discipline*>());
};

#endif // DBASES_H
