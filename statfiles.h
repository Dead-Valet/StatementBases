#pragma once
#include "statementsmanager.h"
#include "statement.h"

#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include "mainwindow.h"

class MainWindow;

class statFiles : public StatementsManager
{
public:
    statFiles();

    void getStatList(QList<Statement*> _statements = QList<Statement*>());
    void addStatement(int _ID, QString _discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner);
    void editStatement(int _ID, QString _discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner);
    void removeStatement(int id);

    QList<Statement*> statements;

    QList<Statement*> load(QString filename, MainWindow *w);
    void save(QString filename, MainWindow *w);

};
