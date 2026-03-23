#include "database_window.h"
#include "ui_database_window.h"

database_window::database_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::database_window)
{
    ui->setupUi(this);
}

database_window::~database_window()
{
    db.close();
    delete ui;
}

void database_window::on_pushButton_clicked()
{
    db.setHostName(ui->Server->toPlainText());
    db.setDatabaseName(ui->Name->toPlainText());
    db.setUserName(ui->User->toPlainText());
    db.setPassword(ui->Password->toPlainText());

    if (!db.open()) {
        QMessageBox ms;
        ms.setWindowTitle(QString());
        ms.setText(db.lastError().text());
        ms.exec();
        return;
    }

    next.setHostName(ui->Server->toPlainText());
    next.setDatabaseName("testbase");
    next.setUserName(ui->User->toPlainText());
    next.setPassword(ui->Password->toPlainText());

    if (next.open()) {
        if (!next.tables().contains("disciplines")) {
            QSqlQuery query;
            QString createTableSQL = "CREATE TABLE disciplines (id SERIAL PRIMARY KEY, name VARCHAR(100) NOT NULL);";
            query.exec(createTableSQL);
        }
    }

    else {
        QSqlQuery query;
        if (query.exec("CREATE DATABASE testbase")) {
            QString createTableSQL = "CREATE TABLE disciplines (id SERIAL PRIMARY KEY, name VARCHAR(100) NOT NULL);";
            query.exec(createTableSQL);
        }
    }

    this->hide();

}
