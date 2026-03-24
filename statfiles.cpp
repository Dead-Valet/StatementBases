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

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    w->table->setRowCount(0);
    w->table->setRowCount(100);
    w->currentRow = -1;
    w->statements.clear();
    statements.clear();

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> i = line.split("; ");
        foreach (Discipline *d, w->disciplines) {
            if (d->name == i[1]) {
                statements.append(new Statement(i[0].toInt(), d, i[2].toInt(), i[3], i[4], i[5], i[6], i[7], i[8].replace(QRegularExpression(","), ";")));
                w->statements.append(new Statement(i[0].toInt(), d, i[2].toInt(), i[3], i[4], i[5], i[6], i[7], i[8].replace(QRegularExpression(","), ";")));
                w->currentRow++;
                for (int j = 0; j < 9; j++) {
                    w->table->setItem(w->currentRow, j, new QTableWidgetItem(i[j]));
                }
                break;
            }
        }
    }
}

void statFiles::save(QString filename, MainWindow *w) {

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    statements.clear();

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
        addStatement(w->table->item(i, 0)->text().toInt(), dis, w->table->item(i, 2)->text().toInt(), w->table->item(i, 3)->text(), w->table->item(i, 4)->text(), w->table->item(i, 5)->text(), w->table->item(i, 6)->text(), w->table->item(i, 7)->text(),  w->table->item(i, 8)->text().replace(QRegularExpression(";"), ","));
    }

    QFile file2("out.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out2(&file2);
    out2 << w->lS << " ";
    out2 << w->lD << "\n";
}
