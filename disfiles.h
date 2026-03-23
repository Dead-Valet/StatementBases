#pragma once

#include "disciplinemanager.h"
#include "discipline.h"

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>

#include "mainwindow.h"

class MainWindow;

class disFiles : public DisciplineManager
{
public:

    disFiles();

    void getDisList(QList<Discipline*> _disciplines = QList<Discipline*>());
    void addDiscipline(int id, QString name);
    void editDiscipline(int id, QString name);
    void removeDiscipline(int id);

    void load(QString filename, MainWindow *w);
    void save(QString filename, MainWindow *w);

    QList<Discipline*> disciplines;

};

