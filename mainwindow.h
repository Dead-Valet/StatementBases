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
#include "tableedit.h"

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
    void EdisStatement(int id);
    void EditDiscipline(int id);
    void RemoveStatement();
    void RemoveDiscipline();

    QTableWidget *table;
    QWidget *stat;
    int currentRow = -1;
    QString mode;

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

    void on_workSpace_cellClicked(int row, int column);

    void on_CancelAdding_clicked();

private:
    Ui::MainWindow *ui;
    void CheckAndDone();
    bool Check(int number, QString data);

};
#endif // MAINWINDOW_H
