#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScrollBar>
#include <regex>
#include <QFrame>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(QGuiApplication::primaryScreen()->size().width(), QGuiApplication::primaryScreen()->size().height());

    table = this->findChild<QTableWidget*>("workSpace");
    table->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    stat = this->findChild<QWidget*>("addStatWid");
    stat->setGeometry(this->geometry().width() / 2 - stat->geometry().width() / 2, this->geometry().height() / 2 - stat->geometry().height() / 2,  stat->geometry().width(), stat->geometry().height());

    dis = this->findChild<QFrame*>("addDisWid");
    dis->setGeometry(this->geometry().width() / 2 - dis->geometry().width() / 2, this->geometry().height() / 2 - dis->geometry().height() / 2,  dis->geometry().width(), dis->geometry().height());

    // MENU BAR

    save = new QAction("Save");
    save->connect(save, &QAction::triggered, this, &MainWindow::saveAct);
    this->menuBar()->addAction(save);

    load = new QAction("Load");
    load->connect(save, &QAction::triggered, this, &MainWindow::loadAct);
    this->menuBar()->addAction(load);

    addDiscipline = new QAction("Add discipline");
    addDiscipline->connect(addDiscipline, &QAction::triggered, this, &MainWindow::addDAct);
    this->menuBar()->addAction(addDiscipline);

    addStatement = new QAction("Add statement");
    addStatement->connect(addStatement, &QAction::triggered, this, &MainWindow::addSAct);
    this->menuBar()->addAction(addStatement);

    findStatement = new QAction("Find statement");
    findStatement->connect(findStatement, &QAction::triggered, this, &MainWindow::findAct);
    this->menuBar()->addAction(findStatement);

    mode = "None";

    stat->setStyleSheet("color: black;");
    dis->setStyleSheet("color: black;");

    stat->setEnabled(false);
    stat->hide();

    dis->setEnabled(false);
    dis->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    table->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    stat->setGeometry(this->geometry().width() / 2 - stat->geometry().width() / 2, this->geometry().height() / 2 - stat->geometry().height() / 2, stat->geometry().width(), stat->geometry().height());
    dis->setGeometry(this->geometry().width() / 2 - dis->geometry().width() / 2, this->geometry().height() / 2 - dis->geometry().height() / 2,  dis->geometry().width(), dis->geometry().height());
}

// MENU ACTIONS

void MainWindow::saveAct() {std::cout << "saved" << std::endl;}

void MainWindow::loadAct() {std::cout << "loaded" << std::endl;}

void MainWindow::addDAct()
{
    table->lower();
    table->setEnabled(false);

    dis->raise();
    dis->setEnabled(true);
    dis->show();
    mode = "Add";
}

void MainWindow::addSAct()
{
    table->lower();
    table->setEnabled(false);

    stat->raise();
    stat->setEnabled(true);
    stat->show();
    mode = "Add";
}

void MainWindow::findAct() {}

// BASE ACTIONS

void MainWindow::EditStatement(int id)
{
    table->lower();
    table->setEnabled(false);

    stat->raise();
    stat->setEnabled(true);
    stat->show();

    mode = "Edit";
    editedId = id;
}

void MainWindow::EditDiscipline(int id)
{
    table->lower();
    table->setEnabled(false);

    dis->raise();
    dis->setEnabled(true);
    dis->show();

    mode = "Edit";
    editedId = id;

}

// Removing

void MainWindow::RemoveStatement(int id) {}
void MainWindow::RemoveDiscipline(int id) {}

// Adding/Editing

bool MainWindow::CheckAndDone()
{
    bool allCorrect = true;

    foreach (QPlainTextEdit *i, stat->findChildren<QPlainTextEdit*>()) {
        if (i->property("Correct") == false) {
            allCorrect = false;
            break;
        }
    }

    if (allCorrect) {

        QList<QPlainTextEdit*> data = stat->findChildren<QPlainTextEdit*>();

        QString discipline = data[0]->toPlainText().simplified();
        int sem = data[1]->toPlainText().toInt();
        QString type = data[2]->toPlainText().simplified();
        QString group = data[3]->toPlainText().simplified();
        QString number = data[4]->toPlainText().simplified();
        QString date = data[5]->toPlainText().simplified();;
        QString date2 = data[6]->toPlainText().simplified();;
        QString owner = data[7]->toPlainText().simplified();

        if (mode == "Add") {
            if (statements.empty()) {statements.append(new Statement(1, discipline, sem, type, group, number, date, date2, owner));}
            else {statements.append(new Statement(statements.last()->ID + 1, discipline, sem, type, group, number, date, date2, owner));}
            std::cout << "stat added" << std::endl;
            return true;
        }
        if (mode == "Edit") {
            foreach (Statement *i, statements) {
                if (i->ID == editedId) {
                    i->sem = sem;
                    i->type = type;
                    i->group = group;
                    i->number = number;
                    i->date = date;
                    i->date2 = date2;
                    i->owner = owner;
                    std::cout << "stat edited" << std::endl;
                    return true;
                }
            }
        }
    }

    std::cout << "incorrect data format" << std::endl;
    return false;
}

bool MainWindow::CheckAndDoneDis()
{
    if (ui->plainTextEdit_9->property("Correct") == true) {

        QString name = ui->plainTextEdit_9->toPlainText().simplified();

        if (mode == "Add")
        {
            if (disciplines.isEmpty()) {
                disciplines.append(new Discipline(name, 1));
            }
            else {
                disciplines.append(new Discipline(name, disciplines.last()->ID + 1));
            }
            std::cout << "dis added" << std::endl;
            return true;
        }
        if (mode == "Edit") {
            foreach (Discipline *i, disciplines) {
                if (i->ID == editedId) {
                    i->name = name;
                    std::cout << "dis edited" << std::endl;
                    return true;
                }
            }
        }
    }
    std::cout << "incorrect data format for discipline" << std::endl;
    return false;
}

void MainWindow::on_workSpace_cellClicked(int row, int column)
{
    std::cout << "clicked" << std::endl;
}

// Cancel

void MainWindow::on_CancelAdding_clicked()
{

    foreach (QPlainTextEdit *i, stat->findChildren<QPlainTextEdit*>()) {
        i->clear();
        i->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

    dis->lower();
    dis->setEnabled(false);
    dis->hide();

    table->raise();
    table->setEnabled(true);
    mode = "None";
}

void MainWindow::on_CancelAdding_2_clicked()
{
    ui->plainTextEdit_9->clear();
    ui->plainTextEdit_9->setProperty("Correct", false);
    ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");


    stat->lower();
    stat->setEnabled(false);
    stat->hide();

    table->raise();
    table->setEnabled(true);
    mode = "None";
}

// Confirm

void MainWindow::on_ConfirmAdding_clicked()
{
    if (CheckAndDone())
    {
        foreach (QPlainTextEdit *i, stat->findChildren<QPlainTextEdit*>()) {
            i->clear();
            i->setStyleSheet("background-color: rgb(255, 255, 255);");
        }

        stat->lower();
        stat->setEnabled(false);
        stat->hide();

        table->raise();
        table->setEnabled(true);
        mode = "None";
    }

}

void MainWindow::on_ConfirmAdding_2_clicked()
{
    if (CheckAndDoneDis())
    {
        dis->lower();
        dis->setEnabled(false);
        dis->hide();

        table->raise();
        table->setEnabled(true);
        mode = "None";
    }
}

// DATA

// Discipline check

void MainWindow::on_plainTextEdit_textChanged()
{
    foreach (Discipline *i, disciplines) {
        if (i->name == ui->plainTextEdit->toPlainText()) {
            ui->plainTextEdit->setProperty("Correct", true);
            ui->plainTextEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
            return;
        }
    }
    ui->plainTextEdit->setProperty("Correct", false);
    ui->plainTextEdit->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Sem check

void MainWindow::on_plainTextEdit_2_textChanged()
{
    std::string data = ui->plainTextEdit_2->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_2->setProperty("Correct", false);
        ui->plainTextEdit_2->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (std::regex_match(data, std::regex("^(\\s)*\\d+(\\s)*$"))) {
        if (std::stoi(data) > 0) {
            ui->plainTextEdit_2->setProperty("Correct", true);
            ui->plainTextEdit_2->setStyleSheet("background-color: rgb(255, 255, 255);");
            return;
        }
    }
    ui->plainTextEdit_2->setProperty("Correct", false);
    ui->plainTextEdit_2->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Type check

void MainWindow::on_plainTextEdit_3_textChanged()
{
    std::string data = ui->plainTextEdit_3->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_3->setProperty("Correct", false);
        ui->plainTextEdit_3->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (std::regex_match(data, std::regex("^(Зачет)|(Экзамен)$"))) {
        ui->plainTextEdit_3->setProperty("Correct", true);
        ui->plainTextEdit_3->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    ui->plainTextEdit_3->setProperty("Correct", false);
    ui->plainTextEdit_3->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Group check

void MainWindow::on_plainTextEdit_4_textChanged()
{
    QString data = ui->plainTextEdit_4->toPlainText();
    if (data.isEmpty()) {
        ui->plainTextEdit_4->setProperty("Correct", false);
        ui->plainTextEdit_4->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (QRegularExpression("^(\\s)*([а-яА-ЯёЁ])+(\\s)*$").match(data).hasMatch()) {
        ui->plainTextEdit_4->setProperty("Correct", true);
        ui->plainTextEdit_4->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    ui->plainTextEdit_4->setProperty("Correct", false);
    ui->plainTextEdit_4->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Number check

void MainWindow::on_plainTextEdit_5_textChanged()
{
    std::string data = ui->plainTextEdit_5->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_5->setProperty("Correct", false);
        ui->plainTextEdit_5->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (std::regex_match(data, std::regex("^(\\s)*\\d+(-\\d+)?(\\s)*$"))) {
        ui->plainTextEdit_5->setProperty("Correct", true);
        ui->plainTextEdit_5->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    ui->plainTextEdit_5->setProperty("Correct", false);
    ui->plainTextEdit_5->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Date getting check

void MainWindow::on_plainTextEdit_6_textChanged()
{
    std::string data = ui->plainTextEdit_6->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_6->setProperty("Correct", false);
        ui->plainTextEdit_6->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (std::regex_match(data, std::regex("^(\\s)*(\\d|([0-2]\\d)|(3[01])).((0\\d)|(1[012])|\\d).((20\\d\\d)|(\\d\\d))(\\s)*$"))) {
        if (QDate(ui->plainTextEdit_6->toPlainText().split('.')[2].toInt(), ui->plainTextEdit_6->toPlainText().split('.')[1].toInt(), ui->plainTextEdit_6->toPlainText().split('.')[0].toInt()).isValid())
        {
            ui->plainTextEdit_6->setProperty("Correct", true);
            ui->plainTextEdit_6->setStyleSheet("background-color: rgb(255, 255, 255);");
            return;
        }
    }
    ui->plainTextEdit_6->setProperty("Correct", false);
    ui->plainTextEdit_6->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Date submitting check

void MainWindow::on_plainTextEdit_7_textChanged()
{
    std::string data = ui->plainTextEdit_7->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_7->setProperty("Correct", false);
        ui->plainTextEdit_7->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (std::regex_match(data, std::regex("^(\\s)*(\\d|([0-2]\\d)|(3[01])).((0\\d)|(1[012])|\\d).((20\\d\\d)|(\\d\\d))(\\s)*$"))) {
        if (QDate(ui->plainTextEdit_7->toPlainText().split('.')[2].toInt(), ui->plainTextEdit_7->toPlainText().split('.')[1].toInt(), ui->plainTextEdit_7->toPlainText().split('.')[0].toInt()).isValid())
        {
            if (ui->plainTextEdit_6->property("Correct") == true) {
                    if (QDate(ui->plainTextEdit_6->toPlainText().split('.')[2].toInt(), ui->plainTextEdit_6->toPlainText().split('.')[1].toInt(), ui->plainTextEdit_6->toPlainText().split('.')[0].toInt()) <=
                    QDate(ui->plainTextEdit_7->toPlainText().split('.')[2].toInt(), ui->plainTextEdit_7->toPlainText().split('.')[1].toInt(), ui->plainTextEdit_7->toPlainText().split('.')[0].toInt())) {
                    ui->plainTextEdit_7->setProperty("Correct", true);
                    ui->plainTextEdit_7->setStyleSheet("background-color: rgb(255, 255, 255);");
                    return;
                }
            }
        }
    }
    ui->plainTextEdit_7->setProperty("Correct", false);
    ui->plainTextEdit_7->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Name check

void MainWindow::on_plainTextEdit_8_textChanged()
{
    QString data = ui->plainTextEdit_8->toPlainText();
    if (data.isEmpty()) {
        ui->plainTextEdit_8->setProperty("Correct", false);
        ui->plainTextEdit_8->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (QRegularExpression("^(\\s)*[А-Я]([а-я])+\\s+[А-Я]([а-я])+(\\s+[А-Я]([а-я])+)?(\\s)*$").match(data).hasMatch()) {
        ui->plainTextEdit_8->setProperty("Correct", true);
        ui->plainTextEdit_8->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    ui->plainTextEdit_8->setProperty("Correct", false);
    ui->plainTextEdit_8->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Discipline Add/Edit check


void MainWindow::on_plainTextEdit_9_textChanged()
{

    QString data = ui->plainTextEdit_9->toPlainText();
    if (data.isEmpty()) {
        ui->plainTextEdit_9->setProperty("Correct", false);
        ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
    }
    if (QRegularExpression("^(\\s)*[А-ЯЁ]([а-яА-ЯёЁ])+(\\s+([а-яА-ЯёЁ])+)*(\\s)*$").match(data).hasMatch()) {
        ui->plainTextEdit_9->setProperty("Correct", true);
        ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    ui->plainTextEdit_9->setProperty("Correct", false);
    ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 123, 123);");
}


