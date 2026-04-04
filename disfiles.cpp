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

void disFiles::load(QString filename, MainWindow *w) {

    w->currentRowDis = -1;
    w->tableDis->setRowCount(0);
    w->tableDis->setRowCount(100);

    foreach (Discipline *i, disciplines) {
        w->currentRowDis++;
        w->tableDis->setItem(w->currentRowDis, 1, new QTableWidgetItem(i->name));
        w->tableDis->setItem(w->currentRowDis, 0, new QTableWidgetItem(QString::number(i->ID)));
    }

}

void disFiles::save(QString filename, MainWindow *w) {

    QFile file("testStorage.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return;
    }
    disciplines.clear();

    QTextStream out(&file);
    for (int i = 0; i <= w->currentRowDis; i++) {
        out << w->tableDis->item(i, 0)->text() << "; " << w->tableDis->item(i, 1)->text() << "\n";
        addDiscipline(w->tableDis->item(i, 0)->text().toInt(), w->tableDis->item(i, 1)->text());
    }

    QFile file2("out.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out2(&file2);
    out2 << w->lS << " ";
    out2 << w->lD << "\n";
}
