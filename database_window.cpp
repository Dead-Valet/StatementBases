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

    if (!db.tables().contains("disciplines")) {
        QSqlQuery query;
        QString createTableSQL = "CREATE TABLE disciplines (id SERIAL PRIMARY KEY, name VARCHAR(100) NOT NULL UNIQUE);";
        if(!query.exec(createTableSQL)) {
            std::cout << "Error creating disciplines: " << query.lastError().text().toStdString() << std::endl;
        }
    }

    if (!db.tables().contains("statements")) {
        QSqlQuery query;
        QString createTableSQL = "CREATE TABLE statements ("
                                 "id SERIAL PRIMARY KEY, "
                                 "discipline VARCHAR(100) NOT NULL,"
                                 "term INT,"
                                 "type VARCHAR(100) NOT NULL,"
                                 "group_ VARCHAR(100) NOT NULL,"
                                 "number VARCHAR(100) NOT NULL,"
                                 "date_getting VARCHAR(100) NOT NULL,"
                                 "date_passing VARCHAR(100) NOT NULL,"
                                 "who_passed VARCHAR(100) NOT NULL,"
                                 "FOREIGN KEY (discipline) REFERENCES disciplines (name) ON DELETE CASCADE);";

        if(!query.exec(createTableSQL)) {
            std::cout << query.lastError().text().toStdString() << std::endl;
        }
    }

    OPENED();

    this->hide();

}
