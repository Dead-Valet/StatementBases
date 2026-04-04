#include "xmlsaver.h"
//#include "discipline.h"

xmlSaver::xmlSaver(QString _filename, MainWindow *win) : filename(_filename), w(win) {}

void xmlSaver::save(disFiles *file) {
    file->save("presaver.txt", w);
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::WriteOnly  | QIODevice::Text)) {return;}
    QTextStream out(&f);
    out << "<table>\n";
    foreach (Discipline *i, file->disciplines) {
        out << "    <tr>\n";
        out << "        <td>" << QString::number(i->ID) << "</td><td>" << i->name << "</td>\n";
        out << "    </tr>\n";
    }
    out << "</table>";
    f.close();

}
void xmlSaver::save(statFiles *file) {
    file->save("presaver.txt", w);
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::WriteOnly  | QIODevice::Text)) {return;}
    QTextStream out(&f);
    out << "<table>\n";
    out << "    </tableColumns>";
    foreach (Statement *i, file->statements) {
        out << "    <tr>\n";
        out << "        <td>" << QString::number(i->ID) << "</td><td>" << i->discipline->name << "</td><td>" << QString::number(i->sem) << "</td><td>" << i->type << "</td><td>" << i->group << "</td><td>" << i->number << "</td><td>" << i->date << "</td><td>" << i->date2 << "</td><td>" << i->owner << "</td>\n";
        out << "    </tr>\n";
    }
    out << "</table>";
    f.close();
}

void xmlSaver::load(disFiles *file) {
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::ReadOnly  | QIODevice::Text)) {return;}
    QTextStream in(&f);
    file->disciplines.clear();
    while (!in.atEnd()) {
        QString str = in.readLine();
        if (str.contains("<td>")) {
            QList<QString> line = str.split("</td><td>");
            file->addDiscipline(line[0].split("<td>")[1].toInt(), line[1].split("</td>")[0]);
            w->disciplines.append(new Discipline(line[0].split("<td>")[1].toInt(), line[1].split("</td>")[0]));
        }
    }
    file->load(filename, w);
}

void xmlSaver::load(statFiles *file) {
    file->statements.clear();
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::ReadOnly  | QIODevice::Text)) {return;}
    QTextStream in(&f);
    file->statements.clear();
    while (!in.atEnd()) {
        QString str = in.readLine();
        if (str.contains("<td>")) {
            QList<QString> line = str.split("</td><td>");
            int j;
            foreach (Discipline *i, w->dbase->disciplines) {
                if (line[2] == i->name) {
                    j = w->dbase->disciplines.indexOf(i);
                    break;
                }
            }
            file->addStatement(line[0].split("<td>")[1].toInt(), w->dbase->disciplines[j], line[2].toInt(), line[3], line[4], line[5], line[6], line[7], QString(line[8].split("</td>")[0]));
            w->statements.append(new Statement(QString(line[0].split("<td>")[1]).toInt(), w->dbase->disciplines[j], QString(line[2]).toInt(), line[3], line[4], line[5], line[6], line[7], line[8].split("</td>")[0]));
        }
    }
    file->load(filename, w);
}
