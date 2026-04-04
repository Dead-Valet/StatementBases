#include "mainwindow.h"
#include "database_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    database_window *db = new database_window();
    db->show();
    MainWindow w(nullptr, db);
    QObject::connect(db, &database_window::OPENED, &w, &MainWindow::show);
    db->raise();
    return a.exec();
}
