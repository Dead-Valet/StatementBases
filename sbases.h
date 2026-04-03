#ifndef SBASES_H
#define SBASES_H

#include "statementsmanager.h"
#include "mainwindow.h"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class MainWindow;

class sbases : public StatementsManager
{
public:
    sbases(MainWindow *win);
    MainWindow *w;
    QSqlDatabase database;
    int id = 0;
    QList<Statement*> statements;
    void addStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner);
    void editStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner);
    void removeStatement(int id);
    QString line(Statement *stat);

public slots:
    void getStatList(QList<Statement*> _statements = QList<Statement*>());
};

#endif // SBASES_H
