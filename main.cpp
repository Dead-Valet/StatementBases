#include "mainwindow.h"
#include "database_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    database_window db;
    db.show();
    MainWindow w(nullptr, db.db);
    w.show();
    return a.exec();
}
