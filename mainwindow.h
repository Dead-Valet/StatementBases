#pragma once

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>

#include <QScreen>
#include <QTableWidget>
#include <QMenuBar>
#include <QAction>
#include <iostream>
#include <QString>
#include <QList>
#include <QScrollBar>
#include <QFrame>
#include <QRegularExpression>
#include <QShortcut>
#include <QKeySequence>
#include <QSlider>
#include <QFile>
#include <QTextStream>
#include <string.h>
#include <regex>
#include <QFileDialog>
#include <QStandardPaths>

#include "discipline.h"
#include "statement.h"
#include "tableedit.h"
#include "statementsmanager.h"
#include "statfiles.h"
#include "disciplinemanager.h"
#include "disfiles.h"
#include "dbases.h"
#include "sbases.h"

#include "xmlsaver.h"

#include "statwindow.h"
#include "diswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class statFiles;
class disFiles;
class StatWindow;
class diswindow;
class dbases;
class sbases;
class xmlSaver;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QSqlDatabase database;

    StatWindow *statWid;
    diswindow *disWid;
    MainWindow(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    ~MainWindow();

    void EditStatement(int row);
    void EditDiscipline(int row);
    void RemoveDiscipline(int row);

    QTableWidget *table;
    QTableWidget *tableDis;

    QWidget *findStat;

    int currentRow = -1;
    int currentRowDis = -1;
    int editedId = 0;
    int editedRow = 0;
    int y = 0;
    QString mode = "None";

    QList<QTableWidgetItem*> results;

    // Menu actions;

    QAction *save;
    QAction *load;
    QAction *addDiscipline;
    QAction *addStatement;
    QAction *findStatement;
    QAction *switchTable;

    QShortcut *shortcut;
    QShortcut *stateShortcut;
    QShortcut *disShortcut;
    QShortcut *findShortcut;

    QList<Discipline*> disciplines;
    QList<Statement*> statements;
    int lS;
    int lD;

    QString findstats;
    QString finddis;

    statFiles *sfile;
    disFiles *dfile;
    QString filename = "testStorage.txt";

    dbases *dbase;
    sbases *sbase;

public slots:

    void resizeEvent(QResizeEvent* event);

    void saveAct();
    void loadAct();
    void addDAct();
    void addSAct();
    void findAct();
    void switchAct();

    void lockMenu();
    void unlockMenu();

    void on_ok_2_clicked();
    void on_ok_clicked();
    void on_findText_textChanged();
    void on_resultsViev_valueChanged(int value);

    void on_workSpace_cellDoubleClicked(int row, int column);
    void on_tableDisWidget_cellDoubleClicked(int row, int column);

private:

    Ui::MainWindow *ui;
};
