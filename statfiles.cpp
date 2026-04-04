#include "statfiles.h"


statFiles::statFiles() {}


void statFiles::getStatList(QList<Statement*> _statements) {
    statements.clear();
    foreach (Statement *i, _statements) {
        statements.append(i);
    }
}

void statFiles::addStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {
    statements.append(new Statement(_ID, _discipline, _sem, _type, _group, _number, _date, _date2, _owner));
}

void statFiles::editStatement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) {
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
            return;
        }
    }
}

void statFiles::removeStatement(int id){
    foreach (Statement *i, statements) {
        if (i->ID == id) {
            statements.remove(statements.indexOf(i));
            return;
        }
    }
}

void statFiles::load(QString filename, MainWindow *w) {

    w->table->setRowCount(0);
    w->table->setRowCount(100);
    w->currentRow = -1;

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
    }
}


void statFiles::save(QString filename, MainWindow *w) {

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << "Ведомости\n";
    for (int i = 0; i <= w->currentRow; i++) {
        Discipline *dis;
        foreach (Discipline *j, w->disciplines) {
            if (j->name == w->table->item(i, 1)->text()) {
                dis = j;
                break;
            }
        }
        out << w->table->item(i, 0)->text() << "; " << w->table->item(i, 1)->text() << "; " <<w->table->item(i, 2)->text() << "; " << w->table->item(i, 3)->text() << "; " << w->table->item(i, 4)->text() << "; " << w->table->item(i, 5)->text() << "; " << w->table->item(i, 6)->text() << "; " << w->table->item(i, 7)->text() << "; " << w->table->item(i, 8)->text().replace(QRegularExpression(";"), ",") << "\n";
    }

    QFile file2("out.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out2(&file2);
    out2 << w->lS << " ";
    out2 << w->lD << "\n";
}
