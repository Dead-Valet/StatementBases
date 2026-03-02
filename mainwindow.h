#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QScreen>
#include <QTableWidget>
#include <QMenuBar>
#include <QAction>
#include <iostream>
#include <QString>
#include <QList>

#include "discipline.h"
#include "statement.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTableWidget *table;

    // Menu actions;

    QAction *save;
    QAction *load;
    QAction *addDiscipline;
    QAction *addStatement;
    QAction *findStatement;

    QList<Discipline> disciplines;
    QList<Statement> statements;


private slots:
    void resizeEvent(QResizeEvent* event);
    void saveAct();
    void loadAct();
    void addDAct();
    void addSAct();
    void findAct();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
