#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(QGuiApplication::primaryScreen()->size().width(), QGuiApplication::primaryScreen()->size().height());

    table = this->findChild<QTableWidget*>("workSpace");
    table->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableDis = this->findChild<QTableWidget*>("tableDisWidget");
    tableDis->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    tableDis->setColumnWidth(0, 70);
    tableDis->setColumnWidth(1, 500);
    tableDis->hide();

    stat = this->findChild<QWidget*>("addStatWid");
    stat->setGeometry(this->geometry().width() / 2 - stat->geometry().width() / 2, this->geometry().height() / 2 - stat->geometry().height() / 2,  stat->geometry().width(), stat->geometry().height());

    dis = this->findChild<QFrame*>("addDisWid");
    dis->setGeometry(this->geometry().width() / 2 - dis->geometry().width() / 2, this->geometry().height() / 2 - dis->geometry().height() / 2,  dis->geometry().width(), dis->geometry().height());

    findStat = this->findChild<QWidget*>("FindStatWid");
    findStat->setGeometry(0, 0, findStat->geometry().width(), findStat->geometry().height());
    findStat->hide();

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

    switchTable = new QAction("Disciplines");
    switchTable->connect(switchTable, &QAction::triggered, this, &MainWindow::switchAct);
    this->menuBar()->addAction(switchTable);

    mode = "None";

    stat->setStyleSheet("color: black;");
    dis->setStyleSheet("color: black;");

    stat->setEnabled(false);
    stat->hide();

    dis->setEnabled(false);
    dis->hide();

    ui->addStatWid->findChild<QPushButton*>("deleteButton")->hide();
    ui->addDisWid->findChild<QPushButton*>("deleteButton_2")->hide();
    ui->addStatWid->findChild<QFrame*>("ConfirmFrame")->hide();
    ui->addDisWid->findChild<QFrame*>("ConfirmFrame_2")->hide();

    // HOTKEY

    shortcut = new QShortcut(QKeySequence("Shift+Tab"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::switchAct);

    stateShortcut = new QShortcut(QKeySequence("Shift+S"), this);
    connect(stateShortcut, &QShortcut::activated, this, &MainWindow::addSAct);

    disShortcut = new QShortcut(QKeySequence("Shift+D"), this);
    connect(disShortcut, &QShortcut::activated, this, &MainWindow::addDAct);


    findShortcut = new QShortcut(QKeySequence("Ctrl+F"), this);
    connect(findShortcut, &QShortcut::activated, this, &MainWindow::findAct);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
    tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
    stat->setGeometry(this->geometry().width() / 2 - stat->geometry().width() / 2, this->geometry().height() / 2 - stat->geometry().height() / 2, stat->geometry().width(), stat->geometry().height());
    dis->setGeometry(this->geometry().width() / 2 - dis->geometry().width() / 2, this->geometry().height() / 2 - dis->geometry().height() / 2,  dis->geometry().width(), dis->geometry().height());
}

void MainWindow::lockMenu() {
    save->setEnabled(false);
    load->setEnabled(false);
    addDiscipline->setEnabled(false);
    addStatement->setEnabled(false);
}

void MainWindow::unlockMenu() {
    save->setEnabled(true);
    load->setEnabled(true);
    addDiscipline->setEnabled(true);
    addStatement->setEnabled(true);
}

// MENU ACTIONS

void MainWindow::switchAct() {
    if (switchTable->text() == "Disciplines") {
        table->hide();
        tableDis->show();
        switchTable->setText("Statements");
    }
    else {
        table->show();
        tableDis->hide();
        switchTable->setText("Disciplines");
    }
}

void MainWindow::saveAct() {std::cout << "saved" << std::endl;}

void MainWindow::loadAct() {std::cout << "loaded" << std::endl;}

void MainWindow::addDAct()
{
    if (mode == "None") {
    lockMenu();
    table->lower();
    table->setEnabled(false);
    tableDis->lower();
    tableDis->setEnabled(false);

    stat->hide();

    dis->raise();
    dis->setEnabled(true);
    dis->show();

    mode = "Add";
    ui->label_18->setText("Добавить дисциплину");
    ui->ConfirmAdding_2->setText("Добавить");
    }
}

void MainWindow::addSAct()
{
    if (mode == "None") {
    lockMenu();
    table->lower();
    table->setEnabled(false);
    tableDis->lower();
    tableDis->setEnabled(false);

    dis->hide();

    stat->raise();
    stat->setEnabled(true);
    stat->show();

    mode = "Add";
    ui->label_9->setText("Добавить ведомость");
    ui->ConfirmAdding->setText("Добавить");
    ui->addStatWid->findChild<QPushButton*>("deleteButton")->hide();
    }
}

void MainWindow::findAct() {
    if (y == 0) {
        y = 30;
        table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
        tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
        findStat->show();
    }
    else {
        y = 0;
        table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
        tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
        if (findStat->findChild<QScrollBar*>("resultsViev")->value() > 0) {
            findStat->findChild<QScrollBar*>("resultsViev")->setValue(findStat->findChild<QScrollBar*>("resultsViev")->value() - 1);
        }
        findStat->hide();
    }
}

// BASE ACTIONS


void MainWindow::on_workSpace_cellDoubleClicked(int row, int column)
{
    if (QApplication::mouseButtons() == Qt::RightButton) {
        EditStatement(row);
    }
}

void MainWindow::on_tableDisWidget_cellDoubleClicked(int row, int column)
{
    if (QApplication::mouseButtons() == Qt::RightButton) {
        EditDiscipline(row);
    }
}

void MainWindow::EditStatement(int row)
{
    if (mode == "None") {
    lockMenu();
    table->lower();
    table->setEnabled(false);
    tableDis->lower();
    tableDis->setEnabled(false);

    stat->raise();
    stat->setEnabled(true);
    stat->show();

    mode = "Edit";
    ui->label_9->setText("Редактировать ведомость");
    ui->ConfirmAdding->setText("Изменить");

    editedId = table->item(row, 0)->text().toInt();
    editedRow = row;

    ui->plainTextEdit->setPlainText(table->item(row, 1)->text());
    ui->plainTextEdit_2->setPlainText(table->item(row, 2)->text());
    ui->plainTextEdit_3->setPlainText(table->item(row, 3)->text());
    ui->plainTextEdit_4->setPlainText(table->item(row, 4)->text());
    ui->plainTextEdit_5->setPlainText(table->item(row, 5)->text());
    ui->plainTextEdit_6->setPlainText(table->item(row, 6)->text());
    ui->plainTextEdit_7->setPlainText(table->item(row, 7)->text());
    ui->plainTextEdit_8->setPlainText(table->item(row, 8)->text());

    ui->addStatWid->findChild<QPushButton*>("deleteButton")->show();
    }
}

void MainWindow::EditDiscipline(int row)
{
    if (mode == "None") {
    lockMenu();
    table->lower();
    table->setEnabled(false);
    tableDis->lower();
    tableDis->setEnabled(false);

    dis->raise();
    dis->setEnabled(true);
    dis->show();

    mode = "Edit";
    editedId = tableDis->item(row, 0)->text().toInt();
    editedRow = row;
    ui->label_18->setText("Редактировать дисциплину");
    ui->ConfirmAdding_2->setText("Изменить");

    ui->plainTextEdit_9->setPlainText(tableDis->item(row, 1)->text());

    ui->addDisWid->findChild<QPushButton*>("deleteButton_2")->show();
    }
}

// Removing

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if ((event->key() == Qt::Key_Delete) && (mode == "None")) {
        if (tableDis->isHidden()) {}
    }
}
void MainWindow::RemoveStatement(int row) {
    foreach (Statement *i, statements) {
        if (i->ID == editedId) {

            statements.remove(statements.indexOf(i));
            table->removeRow(row);
            currentRow--;

            foreach (QPlainTextEdit *i, stat->findChildren<QPlainTextEdit*>()) {
                i->clear();
                i->setProperty("Correct", false);
                i->setStyleSheet("background-color: rgb(255, 255, 255);");
            }

            ui->addStatWid->findChild<QPushButton*>("deleteButton")->hide();
            ui->addStatWid->findChild<QFrame*>("ConfirmFrame")->hide();
            ui->addStatWid->hide();
            editedId = 0;
            editedRow = 0;

            stat->lower();
            stat->setEnabled(false);
            stat->hide();

            table->raise();
            table->setEnabled(true);
            tableDis->raise();
            tableDis->setEnabled(true);

            mode = "None";
            return;
        }
    }
}
void MainWindow::RemoveDiscipline(int row) {
    foreach (Discipline *i, disciplines) {
        if (i->ID == editedId) {

            disciplines.remove(disciplines.indexOf(i));
            tableDis->removeRow(row);
            currentRowDis--;

            ui->addDisWid->findChild<QPushButton*>("deleteButton_2")->hide();
            ui->addDisWid->findChild<QFrame*>("ConfirmFrame_2")->hide();
            ui->addDisWid->hide();

            ui->plainTextEdit_9->clear();
            ui->plainTextEdit_9->setProperty("Correct", false);
            ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");

            dis->lower();
            dis->setEnabled(false);
            dis->hide();

            table->raise();
            table->setEnabled(true);
            tableDis->raise();
            tableDis->setEnabled(true);

            mode = "None";
            return;
        }
    }
}

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

        unlockMenu();

        QList<QPlainTextEdit*> data = stat->findChildren<QPlainTextEdit*>();

        QString discipline = data[0]->toPlainText().simplified();
        int sem = data[1]->toPlainText().toInt();
        QString type = data[2]->toPlainText().simplified();
        QString group = data[3]->toPlainText().simplified();
        QString number = data[4]->toPlainText().simplified();
        QString date = data[6]->toPlainText().simplified();;
        QString date2 = data[5]->toPlainText().simplified();;
        QString owner = data[7]->toPlainText().simplified();

        if (mode == "Add") {
            if (statements.empty()) {statements.append(new Statement(1, discipline, sem, type, group, number, date, date2, owner));}
            else {statements.append(new Statement(statements.last()->ID + 1, discipline, sem, type, group, number, date, date2, owner));}
            std::cout << "stat added" << std::endl;

            currentRow++;
            table->setItem(currentRow, 0, new QTableWidgetItem(QString::number(statements.last()->ID)));
            table->setItem(currentRow, 1, new QTableWidgetItem(discipline));
            table->setItem(currentRow, 2, new QTableWidgetItem(QString::number(sem)));
            table->setItem(currentRow, 3, new QTableWidgetItem(type));
            table->setItem(currentRow, 4, new QTableWidgetItem(group));
            table->setItem(currentRow, 5, new QTableWidgetItem(number));
            table->setItem(currentRow, 6, new QTableWidgetItem(date));
            table->setItem(currentRow, 7, new QTableWidgetItem(date2));
            table->setItem(currentRow, 8, new QTableWidgetItem(owner));

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

                    table->setItem(editedRow, 1, new QTableWidgetItem(discipline));
                    table->setItem(editedRow, 2, new QTableWidgetItem(QString::number(sem)));
                    table->setItem(editedRow, 3, new QTableWidgetItem(type));
                    table->setItem(editedRow, 4, new QTableWidgetItem(group));
                    table->setItem(editedRow, 5, new QTableWidgetItem(number));
                    table->setItem(editedRow, 6, new QTableWidgetItem(date));
                    table->setItem(editedRow, 7, new QTableWidgetItem(date2));
                    table->setItem(editedRow, 8, new QTableWidgetItem(owner));

                    editedRow = 0;
                    editedId = 0;

                    ui->addStatWid->findChild<QPushButton*>("deleteButton")->hide();
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

        unlockMenu();

        QString name = ui->plainTextEdit_9->toPlainText().simplified();

        if (mode == "Add")
        {
            currentRowDis++;
            if (disciplines.isEmpty()) {
                disciplines.append(new Discipline(name, 1));
            }
            else {
                disciplines.append(new Discipline(name, disciplines.last()->ID + 1));
            }
            tableDis->setItem(currentRowDis, 0, new QTableWidgetItem(QString::number(disciplines.last()->ID)));
            tableDis->setItem(currentRowDis, 1, new QTableWidgetItem(name));
            std::cout << "dis added" << std::endl;
            return true;
        }
        if (mode == "Edit") {
            foreach (Discipline *i, disciplines) {
                if (i->ID == editedId) {
                    i->name = name;
                    tableDis->setItem(editedRow, 1, new QTableWidgetItem(name));
                    editedRow = 0;
                    editedId = 0;

                    ui->addDisWid->findChild<QPushButton*>("deleteButton_2")->hide();
                    return true;
                }
            }
        }
    }
    std::cout << "incorrect data format for discipline" << std::endl;
    return false;
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
    tableDis->raise();
    tableDis->setEnabled(true);

    mode = "None";
    editedRow = 0;
    editedId = 0;

    ui->addStatWid->findChild<QPushButton*>("deleteButton")->hide();
    unlockMenu();
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
    tableDis->raise();
    tableDis->setEnabled(true);

    mode = "None";
    editedRow = 0;
    editedId = 0;

    ui->addDisWid->findChild<QPushButton*>("deleteButton_2")->hide();
    unlockMenu();
}

// Confirm

void MainWindow::on_ConfirmAdding_clicked()
{
    if (CheckAndDone())
    {
        foreach (QPlainTextEdit *i, stat->findChildren<QPlainTextEdit*>()) {
            i->clear();
            i->setProperty("Correct", false);
            i->setStyleSheet("background-color: rgb(255, 255, 255);");
        }

        stat->lower();
        stat->setEnabled(false);
        stat->hide();

        table->raise();
        table->setEnabled(true);
        tableDis->raise();
        tableDis->setEnabled(true);

        mode = "None";
    }

}

void MainWindow::on_ConfirmAdding_2_clicked()
{
    if (CheckAndDoneDis())
    {
        ui->plainTextEdit_9->clear();
        ui->plainTextEdit_9->setProperty("Correct", false);
        ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");

        dis->lower();
        dis->setEnabled(false);
        dis->hide();

        table->raise();
        table->setEnabled(true);
        tableDis->raise();
        tableDis->setEnabled(true);

        mode = "None";
    }
}

// DATA

// Discipline check

void MainWindow::on_plainTextEdit_textChanged()
{
    if (QRegularExpression("^(\\s)*[А-ЯЁ]([а-яА-ЯёЁ])+(\\s+(([а-яА-ЯёЁ])+|\\d+))*(\\s)*$").match(ui->plainTextEdit->toPlainText()).hasMatch()) {
        ui->plainTextEdit->setProperty("Correct", true);
        ui->plainTextEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
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
    if (std::regex_match(data, std::regex("^(\\s)*(([0-2]\\d)|(3[01])).((0\\d)|(1[012])).[1-3]\\d(\\s)*$"))) {
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
    if (std::regex_match(data, std::regex("^(\\s)*(([0-2]\\d)|(3[01])).((0\\d)|(1[012])).[1-3]\\d(\\s)*$"))) {
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
    if (QRegularExpression("^((\\s)*[А-Я]([а-я])+\\s+[А-Я]([а-я])+(\\s+[А-Я]([а-я])+)?[;]?(\\s)*(\\n)*(\\s)*)+$").match(data).hasMatch()) {
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

    if (QRegularExpression("^(\\s)*[А-ЯЁ]([а-яА-ЯёЁ])+(\\s+(([а-яА-ЯёЁ])+|\\d+))*(\\s)*$").match(data).hasMatch()) {
        foreach (Discipline *i, disciplines) {
            if (i->name == data.simplified() && (i->ID != editedId)) {
                ui->plainTextEdit_9->setProperty("Correct", false);
                ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 123, 123);");
                return;
            }
        }
        ui->plainTextEdit_9->setProperty("Correct", true);
        ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }

    ui->plainTextEdit_9->setProperty("Correct", false);
    ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 123, 123);");

}

void MainWindow::on_ok_2_clicked()
{
    findAct();
}


void MainWindow::on_ok_clicked()
{
    QPlainTextEdit *line = findStat->findChild<QPlainTextEdit*>("findText");
    if (line->toPlainText().isEmpty()) {
        return;
    }
    results = table->findItems(line->toPlainText().simplified(), Qt::MatchContains);
    if (results.isEmpty()) {
        line->setStyleSheet("background-color: rgb(255, 123, 123);");
    }
    else {
        findStat->findChild<QScrollBar*>("resultsViev")->setMaximum(results.length());
        line->setStyleSheet("background-color: rgb(123, 255, 123);");
    }
}

void MainWindow::on_findText_textChanged()
{
    findStat->findChild<QPlainTextEdit*>("findText")->setStyleSheet("background-color: rgb(255, 255, 255);");
    findStat->findChild<QScrollBar*>("resultsViev")->setMaximum(0);
    results.clear();
}

void MainWindow::on_resultsViev_valueChanged(int value)
{
    if (results.isEmpty()) {return;}
    int index = value - 1;
    if (index >= 0) {table->selectRow(results[index]->row());}
}

// Confirming/Canceling deliting

void MainWindow::on_noDel_clicked()
{
    ui->addStatWid->findChild<QFrame*>("ConfirmFrame")->hide();
}

void MainWindow::on_noDel_2_clicked()
{
    ui->addDisWid->findChild<QFrame*>("ConfirmFrame_2")->hide();
}

void MainWindow::on_del_clicked()
{
    RemoveStatement(editedRow);
}

void MainWindow::on_del_2_clicked()
{
    RemoveDiscipline(editedRow);
}

void MainWindow::on_deleteButton_clicked()
{
    ui->addStatWid->findChild<QFrame*>("ConfirmFrame")->show();
}

void MainWindow::on_deleteButton_2_clicked()
{
    ui->addDisWid->findChild<QFrame*>("ConfirmFrame_2")->show();
}
