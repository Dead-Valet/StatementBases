#include "dbases.h"

dbases::dbases(MainWindow *win) : w(win) {
    database = w->database;
}
void dbases::getDisList(QList<Discipline*> _disciplines) {}
void dbases::addDiscipline(int id, QString name) {}
void dbases::editDiscipline(int id, QString name) {}
void dbases::removeDiscipline(int id) {}
