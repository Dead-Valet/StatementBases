#ifndef DISWINDOW_H
#define DISWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <QString>
#include <QList>
#include <QFrame>
#include <QRegularExpression>
#include <QMessageBox>

#include "discipline.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
    class diswindow;
}

class diswindow : public QMainWindow
{
    Q_OBJECT

public:
    bool CheckAndDoneDis();
    void switchText(QString text, bool hided);
    explicit diswindow(QWidget *parent = nullptr, MainWindow *win = nullptr);
    QString mode = "None";
    MainWindow *w;
    Ui::diswindow *ui;

signals:

public slots:

    void on_CancelAdding_2_clicked();
    void on_ConfirmAdding_2_clicked();

    void on_plainTextEdit_9_textChanged();

    void on_deleteButton_2_clicked();

private slots:

private:
    void RemoveDiscipline(int row);
    void closeEvent(QCloseEvent *event);
};

#endif // DISWINDOW_H
