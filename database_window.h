#ifndef DATABASE_WINDOW_H
#define DATABASE_WINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSql>
#include <QSqlError>
#include <QPlainTextEdit>
#include <iostream>
#include <QMessageBox>
#include <QSqlQuery>

namespace Ui {
class database_window;
}

class database_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit database_window(QWidget *parent = nullptr);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    ~database_window();

private slots:
    void on_pushButton_clicked();

signals:
    void OPENED();

private:
    Ui::database_window *ui;
};

#endif // DATABASE_WINDOW_H
