#ifndef STATWINDOW_H
#define STATWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>

#include <iostream>
#include <QString>
#include <QList>
#include <QFrame>
#include <QRegularExpression>
#include <QMessageBox>

#include "mainwindow.h"

class MainWindow;


QT_BEGIN_NAMESPACE
namespace Ui {
class StatWindow;
}
QT_END_NAMESPACE


class StatWindow : public QMainWindow

{
    Q_OBJECT
public:
    bool CheckAndDone();
    void switchText(QString text, bool hided);
    explicit StatWindow(QWidget *parent = nullptr, MainWindow *win = nullptr);
    QString mode = "None";
    MainWindow *w;
    Ui::StatWindow *ui;

signals:

public slots:

    void on_CancelAdding_clicked();
    void on_ConfirmAdding_clicked();

    void on_plainTextEdit_textChanged();
    void on_plainTextEdit_2_textChanged();
    void on_plainTextEdit_3_textChanged();
    void on_plainTextEdit_4_textChanged();
    void on_plainTextEdit_5_textChanged();
    void on_plainTextEdit_6_textChanged();
    void on_plainTextEdit_7_textChanged();
    void on_plainTextEdit_8_textChanged();

    void on_deleteButton_clicked();

private:
    void RemoveStatement(int row);
    void closeEvent(QCloseEvent *event);
};

#endif // STATWINDOW_H
