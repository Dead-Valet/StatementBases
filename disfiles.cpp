#include "disfiles.h"

disFiles::disFiles() {}

void disFiles::getDisList(QList<Discipline*> _disciplines) {
    disciplines.clear();
    foreach (Discipline *i, _disciplines) {
        disciplines.append(i);
    }
}

void disFiles::addDiscipline(int id, QString name) {
    disciplines.append(new Discipline(id, name));
}

void disFiles::editDiscipline(int id, QString name) {
    foreach (Discipline *i, disciplines) {
        if (i->ID == id) {
            i->name = name;
            return;
        }
    }
}

void disFiles::removeDiscipline(int id) {
    foreach (Discipline *i, disciplines) {
        if (i->ID == id) {
            disciplines.remove(disciplines.indexOf(i));
            return;
        }
    }
}

QList<Discipline*> disFiles::load(QString filename, MainWindow *w) {

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {return disciplines;}

    w->currentRowDis = -1;
    w->tableDis->clear();
    w->disciplines.clear();
    disciplines.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> i = line.split(" & ");
        disciplines.append(new Discipline(i[0].toInt(), i[1]));
        w->disciplines.append(new Discipline(i[0].toInt(), i[1]));
        w->currentRowDis++;
        w->tableDis->setItem(w->currentRowDis, 1, new QTableWidgetItem(i[1]));
        w->tableDis->setItem(w->currentRowDis, 0, new QTableWidgetItem(i[0]));
    }
    return disciplines;

}

void disFiles::save(QString filename, MainWindow *w) {

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    foreach (Discipline *i, disciplines) {
        out << QString::number(i->ID) << " & " << i->name << "\n";
    }

    QFile file2("out.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out2(&file2);
    out2 << w->lS << " ";
    out2 << w->lD << "\n";
}
