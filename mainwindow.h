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

#include <string.h>

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

    void EditStatement(int id);
    void EditDiscipline(int id);
    void RemoveStatement(int id);
    void RemoveDiscipline(int id);

    QTableWidget *table;
    QWidget *stat;
    QFrame *dis;
    int currentRow = -1;
    int currentRowDis = -1;
    int editedId = 0;
    QString mode;

    // Menu actions;

    QAction *save;
    QAction *load;
    QAction *addDiscipline;
    QAction *addStatement;
    QAction *findStatement;

    QList<Discipline*> disciplines;
    QList<Statement*> statements;

private slots:

    void resizeEvent(QResizeEvent* event);

    void saveAct();
    void loadAct();
    void addDAct();
    void addSAct();
    void findAct();

    void on_workSpace_cellClicked(int row, int column);

    void on_CancelAdding_clicked();

    void on_plainTextEdit_textChanged();
    void on_plainTextEdit_2_textChanged();
    void on_plainTextEdit_3_textChanged();
    void on_plainTextEdit_4_textChanged();
    void on_plainTextEdit_5_textChanged();
    void on_plainTextEdit_6_textChanged();
    void on_plainTextEdit_7_textChanged();
    void on_plainTextEdit_8_textChanged();

    void on_ConfirmAdding_clicked();

    void on_plainTextEdit_9_textChanged();

    void on_CancelAdding_2_clicked();

    void on_ConfirmAdding_2_clicked();

private:

    Ui::MainWindow *ui;
    bool CheckAndDone();
    bool CheckAndDoneDis();

};
#endif // MAINWINDOW_H
