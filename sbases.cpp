#include "sbases.h"
#include <iostream>

sbases::sbases(MainWindow *win) : w(win) {
    database = w->database;
}

void sbases::getStatList(QList<Statement*> _statements) {

}

void sbases::addStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {


    QSqlQuery query;
    query.prepare("INSERT INTO statements (discipline, term, type, group, number, date_getting, date_passing, who_passed) VALUES (:discipline, :term, :type, :group, :number, :date_getting, :date_passing, :who_passed)");
    query.bindValue(":discipline", _discipline->name);
    query.bindValue(":term", _sem);
    query.bindValue(":type", _type);
    query.bindValue(":group", _group);
    query.bindValue(":number", _number);
    query.bindValue(":date_passing", _date);
    query.bindValue(":date_passed", _date2);
    query.bindValue(":owner", _owner);

    if (query.exec()) {
        id = query.lastInsertId().toInt();
    }

    statements.append(new Statement(id, _discipline, _sem, _type, _group, _number, _date, _date2, _owner));

}
void sbases::editStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {

}
void sbases::removeStatement(int id) {

}

QString sbases::line(Statement *stat) {
    return QString("Test");
}
