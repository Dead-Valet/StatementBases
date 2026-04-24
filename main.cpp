#include "mainwindow.h"
#include "database_window.h"
#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QColor>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette lightPalette;

    lightPalette.setColor(QPalette::Window, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(230, 230, 230));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::red);
    lightPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);

    a.setPalette(lightPalette);

    database_window *db = new database_window();
    db->show();
    MainWindow w(nullptr, db);
    QObject::connect(db, &database_window::OPENED, &w, &MainWindow::show);
    db->raise();
    return a.exec();
}
