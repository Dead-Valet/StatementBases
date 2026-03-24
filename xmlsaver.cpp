#include "xmlsaver.h"

xmlSaver::xmlSaver(QString _filename, MainWindow *win) : filename(_filename), w(win) {}

void xmlSaver::save(disFiles *file) {
    file->save("presaver.txt", w);
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::WriteOnly  | QIODevice::Text)) {return;}
    QTextStream out(&f);
    out << "<table/>";
    out << "    <tr/>";
    out << "        <td>id</td><td>название</td>";
    out << "    </tr>";
    /*
     * out << "    <tableColumns count=\"2\">";
    out << "        <tableColumn id=\"1\" name=\"id\">";
    out << "        <tableColumn id=\"2\" name=\"name\">";
    out << "    </tableColumns>";
    */
    foreach (Discipline *i, file->disciplines) {
        out << "    <tr/>";
        out << "        <td>" << QString::number(i->ID) << "</td><td>" << i->name << "</td>";
        out << "    </tr>";
    }
    out << "/table";
    f.close();

}
void xmlSaver::save(statFiles *file) {
    file->save("presaver.txt", w);
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::WriteOnly  | QIODevice::Text)) {return;}
    QTextStream out(&f);
    out << "<table>\n";
    out << "<list1>\n";
    /*
    out << "    <tr>\n";
    out << "        <td>id</td><td>дисциплина</td><td>семестр</td><td>тип отчетности</td><td>группа</td><td>номер</td><td>дата получения</td><td>дата сдачи</td><td>кто сдал</td>\n";
    out << "    </tr>\n";
    */
    out << "    <tableColumns count=\"9\">\n";
    out << "        <tableColumn id=\"1\" name=\"id\">\n";
    out << "        <tableColumn id=\"2\" name=\"discipline\">\n";
    out << "        <tableColumn id=\"3\" name=\"sem\">\n";
    out << "        <tableColumn id=\"4\" name=\"mark_type\">\n";
    out << "        <tableColumn id=\"5\" name=\"group\">\n";
    out << "        <tableColumn id=\"6\" name=\"number\">\n";
    out << "        <tableColumn id=\"7\" name=\"date_getting\">\n";
    out << "        <tableColumn id=\"8\" name=\"date_passing\">\n";
    out << "        <tableColumn id=\"9\" name=\"names_passed\">\n";
    out << "    </tableColumns>";
    foreach (Statement *i, file->statements) {
        out << "    <tr>\n";
        out << "        <td>" << QString::number(i->ID) << "</td><td>" << i->discipline->name << "</td><td>" << QString::number(i->sem) << "</td><td>" << i->type << "</td><td>" << i->group << "</td><td>" << i->number << "</td><td>" << i->date << "</td><td>" << i->date2 << "</td><td>" << i->owner << "</td>\n";
        out << "    </tr>\n";
    }
    out << "</list1>\n";
    out << "</table>";
    f.close();
}
