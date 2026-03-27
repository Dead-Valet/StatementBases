#include "sbases.h"

sbases::sbases(MainWindow *win) : w(win) {
    database = w->database;
}

void sbases::getStatList(QList<Statement*> _statements) {

}
void sbases::addStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {
    //добавление в базу
    statements.append(new Statement(_ID, _discipline, _sem, _type, _group, _number, _date, _date2, _owner));
}
void sbases::editStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {

}
void sbases::removeStatement(int id) {

}

QString sbases::line(Statement *stat) {
    return QString("Test");
}
