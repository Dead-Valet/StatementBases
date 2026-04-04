#include "dbases.h"
#include <QString>
#include <iostream>

dbases::dbases(MainWindow *win) : w(win) {
    database = w->database;
}
void dbases::getDisList(QList<Discipline*> _disciplines) {

    QSqlQuery query;
    if (!query.exec("SELECT id, name FROM disciplines;")) {
        std::cout << "loh" << std::endl;}
    while (query.next()) {
        id = query.value(0).toInt();
        _name = query.value(1).toString();
        disciplines.append(new Discipline(id, _name));
    }
}

void dbases::addDiscipline(int id, QString name) {
    QSqlQuery query;
    query.prepare("INSERT INTO disciplines (name) VALUES (:name)");
    query.bindValue(":name", name);
    query.exec();
    id = query.lastInsertId().toInt();
    disciplines.append(new Discipline(id, name));
}

void dbases::editDiscipline(int id, QString name) {
    QSqlQuery query;
    query.prepare("UPDATE disciplines SET name = :name WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    query.exec();
    foreach (Discipline *i, disciplines) {
        if (i->ID == id) {
            i->name = name;
        }
    }
}

void dbases::removeDiscipline(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM disciplines WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    foreach (Discipline *i, disciplines) {
        if (i->ID == id) {
            disciplines.remove(disciplines.indexOf(i));
        }
    }
}

void dbases::loadAll() {

    w->tableDis->setRowCount(0);
    w->tableDis->setRowCount(100);
    w->currentRowDis = -1;

    foreach (Discipline *i, disciplines) {
        w->currentRowDis++;
        w->tableDis->setItem(w->currentRowDis, 1, new QTableWidgetItem(i->name));
        w->tableDis->setItem(w->currentRowDis, 0, new QTableWidgetItem(QString::number(i->ID)));
        w->dfile->addDiscipline(i->ID, i->name);
        w->disciplines.append(new Discipline(i->ID, i->name));
    }
}

QString dbases::line(Discipline *dis) {
    return QString(QString::number(dis->ID) + dis->name);
}
