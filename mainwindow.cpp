#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(QGuiApplication::primaryScreen()->size().width(), QGuiApplication::primaryScreen()->size().height());

    statWid = new StatWindow(nullptr, this);
    disWid = new diswindow(nullptr, this);

    table = this->findChild<QTableWidget*>("workSpace");
    table->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableDis = this->findChild<QTableWidget*>("tableDisWidget");
    tableDis->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    tableDis->setColumnWidth(0, 70);
    tableDis->setColumnWidth(1, 500);
    tableDis->hide();

    findStat = this->findChild<QWidget*>("FindStatWid");
    findStat->setGeometry(0, 0, findStat->geometry().width(), findStat->geometry().height());
    findStat->hide();

    sfile = new statFiles();
    dfile = new disFiles();

    // MENU BAR

    save = new QAction("Save");
    save->connect(save, &QAction::triggered, this, &MainWindow::saveAct);
    this->menuBar()->addAction(save);

    load = new QAction("Load");
    load->connect(load, &QAction::triggered, this, &MainWindow::loadAct);
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

    // HOTKEY

    shortcut = new QShortcut(QKeySequence("Shift+Tab"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::switchAct);

    stateShortcut = new QShortcut(QKeySequence("Shift+S"), this);
    connect(stateShortcut, &QShortcut::activated, this, &MainWindow::addSAct);

    disShortcut = new QShortcut(QKeySequence("Shift+D"), this);
    connect(disShortcut, &QShortcut::activated, this, &MainWindow::addDAct);

    findShortcut = new QShortcut(QKeySequence("Ctrl+F"), this);
    connect(findShortcut, &QShortcut::activated, this, &MainWindow::findAct);

    QFile file("out.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        lS = QString(line.split(" ")[0]).toInt();
        lD = QString(line.split(" ")[1]).toInt();
    }
    else {
        QFile file2("out.txt");
        if (file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out2(&file2);
            out2 << "0 0\n";
            lS = 0;
            lD = 0;
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
    tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
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

// SAVE/LOAD

void MainWindow::saveAct() {
    sfile->save(filename, this);
}

void MainWindow::loadAct() {
    sfile->load(filename, this);
}

// ADDING

void MainWindow::addDAct()
{
    if (mode == "None") {
        lockMenu();
        table->setEnabled(false);
        tableDis->setEnabled(false);
        disWid->show();
        disWid->mode = "Add";
        mode = "Add";
        disWid->switchText("Добавить дисциплину", true);
    }
}

void MainWindow::addSAct()
{
    if (mode == "None") {
        lockMenu();
        table->setEnabled(false);
        tableDis->setEnabled(false);

        statWid->show();
        statWid->switchText("Добавить ведомость", true);
        statWid->mode = "Add";
        mode = "Add";
    }
}

// FINDING

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
    if (mode == "saveAs") {}
    if (mode == "load") {}
    if (mode == "None") {}
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
        editedId = table->item(row, 0)->text().toInt();
        editedRow = row;
        statWid->show();
        statWid->switchText("Редактировать ведомость", false);
        statWid->mode = "Edit";
        mode = "Edit";
    }
}

void MainWindow::EditDiscipline(int row)
{
    if (mode == "None") {
        lockMenu();
        table->setEnabled(false);
        tableDis->setEnabled(false);
        mode = "Edit";
        disWid->mode = "Edit";
        editedId = tableDis->item(row, 0)->text().toInt();
        editedRow = row;
        disWid->switchText("Редактировать дисциплину", false);
        disWid->show();
    }
}

// Discipline Add/Edit check

void MainWindow::on_ok_2_clicked()
{
    findAct();
}


void MainWindow::on_ok_clicked()
{
    if ((mode != "load") && (mode != "SaveAs")) {
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
    if (mode == "saveAs") {saveAct();}
    if (mode == "load") {loadAct();}
}

void MainWindow::on_findText_textChanged()
{
    if ((mode != "load") && (mode != "SaveAs")) {
        findStat->findChild<QPlainTextEdit*>("findText")->setStyleSheet("background-color: rgb(255, 255, 255);");
        findStat->findChild<QScrollBar*>("resultsViev")->setMaximum(0);
        results.clear();
    }
}

void MainWindow::on_resultsViev_valueChanged(int value)
{
    if (results.isEmpty()) {return;}
    int index = value - 1;
    if (index >= 0) {table->selectRow(results[index]->row());}
}

