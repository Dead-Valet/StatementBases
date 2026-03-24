#include "dbases.h"
#include <QString>
#include <iostream>

dbases::dbases(MainWindow *win) : w(win) {
    database = w->database;
}
void dbases::getDisList(QList<Discipline*> _disciplines) {}
void dbases::addDiscipline(int id, QString name) {
    QSqlQuery query;
    query.prepare("INSERT INTO disciplines (name) VALUES (:name)");
    query.bindValue(":name", name);
    // вытащиь id из базы
    disciplines.append(new Discipline(id, name));

}
void dbases::editDiscipline(int id, QString name) {}
void dbases::removeDiscipline(int id) {}
