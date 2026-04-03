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
        return this->on_pushButton_clicked();

        if (!db.tables().contains("disciplines")) {
            QSqlQuery query;
            QString createTableSQL = "CREATE TABLE disciplines (id SERIAL PRIMARY KEY AUTO_INCREMENT, name VARCHAR(100) NOT NULL);";
            query.exec(createTableSQL);
        }
        if (!db.tables().contains("statements")) {
            QSqlQuery query;
            QString createTableSQL = "CREATE TABLE statements ("
                                     "id SERIAL PRIMARY KEY, "
                                     "FOREIGN KEY (discipline) REFERENCES disciplines (name),"
                                     "term INT,"
                                     "type INT,"
                                     "group VARCHAR(100) NOT NULL,"
                                     "number VARCHAR(100) NOT NULL,"
                                     "date_getting Date,"
                                     "date_passing Date,"
                                     "who_passed VARCHAR(100) NOT NULL);";
            if(!query.exec(createTableSQL)) {std::cout << db.lastError().text().toStdString() << std::endl;}
        }

        OPENED();

        return;
    }

    if (!db.tables().contains("disciplines")) {
        QSqlQuery query;
        QString createTableSQL = "CREATE TABLE disciplines (id SERIAL PRIMARY KEY AUTO_INCREMENT, name VARCHAR(100) NOT NULL);";
        query.exec(createTableSQL);
    }
    if (!db.tables().contains("statements")) {
        QSqlQuery query;
        QString createTableSQL = "CREATE TABLE statements ("
                                 "id SERIAL PRIMARY KEY, "
                                 "FOREIGN KEY (discipline) REFERENCES disciplines (name),"
                                 "term INT,"
                                 "type INT,"
                                 "group VARCHAR(100) NOT NULL,"
                                 "number VARCHAR(100) NOT NULL,"
                                 "date_getting Date,"
                                 "date_passing Date,"
                                 "who_passed VARCHAR(100) NOT NULL);";
        if(!query.exec(createTableSQL)) {}
    }

    OPENED();

    this->hide();

}
