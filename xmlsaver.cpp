#include "xmlsaver.h"

xmlSaver::xmlSaver(QString filename, MainWindow *win) : file(filename), w(win) {}

void xmlSaver::save(disFiles *file) {
    file->save("presaver.txt", w);
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::WriteOnly  | QIODevice::Text)) {return;}
    QTextStream out(&file);
    out << "<table/>";
    out << "    <tableColumns count=\"2\">";
    out << "        <tableColumn id=\"1\" name=\"id\">";
    out << "        <tableColumn id=\"2\" name=\"name\">";
    out << "    </tableColumns>";
    foreach (Discipline *i, file->statements) {
        out << "    <tr/>";
        out << "        <td/><" << QString::number(i->ID) << "><" << i->name << "></td>";
        out << "    </tr>";
    }
    out << "/table";
    f.close();

}
void xmlSaver::save(statFiles *file) {
    file->save("presaver.txt", w);
    QFile f(filename);
    if (!f.open(QIODevice::QIODevice::WriteOnly  | QIODevice::Text)) {return;}
    QTextStream out(&file);
    out << "<table/>";
    out << "    <tableColumns count=\"9\">";
    out << "        <tableColumn id=\"1\" name=\"id\">";
    out << "        <tableColumn id=\"2\" name=\"discipline\">";
    out << "        <tableColumn id=\"3\" name=\"sem\">";
    out << "        <tableColumn id=\"4\" name=\"mark_type\">";
    out << "        <tableColumn id=\"5\" name=\"group\">";
    out << "        <tableColumn id=\"6\" name=\"number\">";
    out << "        <tableColumn id=\"7\" name=\"date_getting\">";
    out << "        <tableColumn id=\"8\" name=\"date_passing\">";
    out << "        <tableColumn id=\"9\" name=\"names_passed\">";
    out << "    </tableColumns>";
    foreach (Statement *i, file->statements) {
        out << "    <tr/>";
        out << "        <td/><" << QString::number(i->ID) << "><" << i->discipline->name << "><" << QString::number(i->sem) << "><" << i->type << "><" << i->group << "><" << i->number << "><" << i->date << "><" << i->date2 << "><" << i->owner << "></td>";
        out << "    </tr>";
    }
    out << "/table";
    f.close();
}
