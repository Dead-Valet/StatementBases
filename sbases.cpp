#include "sbases.h"
#include <iostream>

sbases::sbases(MainWindow *win) : w(win) {
    database = w->database;
}

void sbases::getStatList(QList<Statement*> _statements) {

    QSqlQuery query;
    if (!query.exec("SELECT id, discipline, term, type, group_, number, date_getting, date_passing, who_passed FROM statements;")) {
        std::cout << "loh" << std::endl;}

    while (query.next()) {

        int _ID = query.value(0).toInt();

        QString name = query.value(1).toString();
        Discipline *_discipline;
        foreach (Discipline *i, w->dbase->disciplines) {
            if (i->name == name) {
                _discipline = i;
                break;
            }
        }

        int _sem = query.value(2).toInt();
        QString _type = query.value(3).toString();
        QString _group = query.value(4).toString();
        QString _number = query.value(5).toString();
        QString _date = query.value(6).toString();
        QString _date2 = query.value(7).toString();
        QString _owner = query.value(8).toString();

        statements.append(new Statement(_ID, _discipline, _sem, _type, _group, _number, _date, _date2, _owner));
    }

}

void sbases::addStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {


    QSqlQuery query;
    query.prepare("INSERT INTO statements (discipline, term, type, group_, number, date_getting, date_passing, who_passed) VALUES (:discipline, :term, :type, :group_, :number, :date_getting, :date_passing, :who_passed)");
    query.bindValue(":discipline", _discipline->name);
    query.bindValue(":term", _sem);
    query.bindValue(":type", _type);
    query.bindValue(":group_", _group);
    query.bindValue(":number", _number);
    query.bindValue(":date_getting", _date);
    query.bindValue(":date_passing", _date2);
    query.bindValue(":who_passed", _owner);

    if (query.exec()) {
        id = query.lastInsertId().toInt();
    }

    statements.append(new Statement(id, _discipline, _sem, _type, _group, _number, _date, _date2, _owner));

}
void sbases::editStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {

    QSqlQuery query;
    query.prepare("UPDATE statements SET discipline = :discipline, term = :term, type = :type, group_ = :group_, number = :number, date_getting = :date_getting, date_passing = :date_passing, who_passed = :who_passed WHERE id = :id");
    query.bindValue(":discipline", _discipline->name);
    query.bindValue(":term", _sem);
    query.bindValue(":type", _type);
    query.bindValue(":group_", _group);
    query.bindValue(":number", _number);
    query.bindValue(":date_getting", _date);
    query.bindValue(":date_passing", _date2);
    query.bindValue(":who_passed", _owner);
    query.bindValue(":id", _ID);

    foreach (Statement *i, statements) {
        if (i->ID == _ID) {
            i->discipline = _discipline;
            i->sem = _sem;
            i->type = _type;
            i->group = _group;
            i->number = _number;
            i->date = _date;
            i->date2 = _date2;
            i->owner = _owner;
            break;
        }
    }

}
void sbases::removeStatement(int id) {

        QSqlQuery query;
        query.prepare("DELETE FROM statements  WHERE id = :id");
        query.bindValue(":id", id);
        query.exec();
        foreach (Statement *i, statements) {
            if (i->ID == id) {
                statements.remove(statements.indexOf(i));
            }
        }

}

void sbases::loadAll() {

    w->table->setRowCount(0);
    w->table->setRowCount(100);
    w->currentRow = -1;
    w->sfile->statements.clear();
    w->statements.clear();

    foreach (Statement *i, statements) {
        w->currentRow++;
        w->table->setItem(w->currentRow, 0, new QTableWidgetItem(QString::number(i->ID)));
        w->table->setItem(w->currentRow, 1, new QTableWidgetItem(i->discipline->name));
        w->table->setItem(w->currentRow, 2, new QTableWidgetItem(QString::number(i->sem)));
        w->table->setItem(w->currentRow, 3, new QTableWidgetItem(i->type));
        w->table->setItem(w->currentRow, 4, new QTableWidgetItem(i->group));
        w->table->setItem(w->currentRow, 5, new QTableWidgetItem(i->number));
        w->table->setItem(w->currentRow, 6, new QTableWidgetItem(i->date));
        w->table->setItem(w->currentRow, 7, new QTableWidgetItem(i->date2));
        w->table->setItem(w->currentRow, 8, new QTableWidgetItem(i->owner));
        w->sfile->addStatement(i->ID, i->discipline, i->sem, i->type, i->group, i->number, i->date, i->date2, i->owner);
        w->statements.append(new Statement(i->ID, i->discipline, i->sem, i->type, i->group, i->number, i->date, i->date2, i->owner));
    }
}

QString sbases::line(Statement *stat) {
    return QString(QString::number(stat->ID) + stat->discipline->name + QString::number(stat->sem) + stat->type + stat->group + stat->number + stat->date + stat->date2 + stat->owner);
}
