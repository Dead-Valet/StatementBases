#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, database_window *db)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), database(db->db)
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

    dfile = new disFiles();
    sfile = new statFiles();

    sbase = new sbases(this);
    dbase = new dbases(this);

    connect(db, &database_window::OPENED, this, [this]() {
        dbase->getDisList();
    });

    connect(db, &database_window::OPENED,this, [this]() {
        sbase->getStatList();
    });

    // MENU BAR

    save = new QAction("Save");
    save->connect(save, &QAction::triggered, this, &MainWindow::saveAct);
    this->menuBar()->addAction(save);

    load = new QAction("Load");
    load->connect(load, &QAction::triggered, this, &MainWindow::loadAct);
    this->menuBar()->addAction(load);

    loadall = new QAction("Load all");
    loadall->connect(loadall, &QAction::triggered, this, &MainWindow::loadAll);
    this->menuBar()->addAction(loadall);

    addDiscipline = new QAction("Add discipline");
    addDiscipline->connect(addDiscipline, &QAction::triggered, this, &MainWindow::addDAct);
    this->menuBar()->addAction(addDiscipline);

    addStatement = new QAction("Add statement");
    addStatement->connect(addStatement, &QAction::triggered, this, &MainWindow::addSAct);
    this->menuBar()->addAction(addStatement);

    findStatement = new QAction("Find");
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
    y = 0;
    table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
    tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
    findStat->hide();
    if (switchTable->text() == "Disciplines") {
        table->hide();
        tableDis->show();
        switchTable->setText("Statements");
        ui->findText->setPlainText(finddis);
        if (!finddis.isEmpty()) {
            y = 30;
            table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
            tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
            findStat->show();
            on_ok_clicked();
        }
    }
    else {
        table->show();
        tableDis->hide();
        switchTable->setText("Disciplines");
        ui->findText->setPlainText(findstats);
        if (!findstats.isEmpty()) {
            y = 30;
            table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
            tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
            findStat->show();
            on_ok_clicked();
        }
    }
}

// SAVE/LOAD

void MainWindow::saveAct() {
    filename = QFileDialog::getOpenFileName();
    xmlSaver *saver = new xmlSaver(filename, this);
    saver->save(sfile);
    saver->save(dfile);
    delete saver;
}

void MainWindow::loadAct() {
    filename = QFileDialog::getOpenFileName();
    xmlSaver *saver = new xmlSaver(filename, this);
    saver->load(sfile);
    saver->load(dfile);
    delete saver;
}

void MainWindow::loadAll() {
    dbase->loadAll();
    sbase->loadAll();
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
        if (switchTable->text() == "Disciplines") {
            table->setRowCount(0);
            table->setRowCount(100);
            currentRow = -1;
            foreach (Statement *i, statements) {
                currentRow++;
                table->setItem(currentRow, 0, new QTableWidgetItem(QString::number(i->ID)));
                table->setItem(currentRow, 1, new QTableWidgetItem(i->discipline->name));
                table->setItem(currentRow, 2, new QTableWidgetItem(QString::number(i->sem)));
                table->setItem(currentRow, 3, new QTableWidgetItem(i->type));
                table->setItem(currentRow, 4, new QTableWidgetItem(i->group));
                table->setItem(currentRow, 5, new QTableWidgetItem(i->number));
                table->setItem(currentRow, 6, new QTableWidgetItem(i->date));
                table->setItem(currentRow, 7, new QTableWidgetItem(i->date2));
                table->setItem(currentRow, 8, new QTableWidgetItem(i->owner));
            }
            findstats = QString();
        }
        else {
            tableDis->setRowCount(0);
            tableDis->setRowCount(100);
            currentRowDis = -1;
            foreach (Discipline *i, disciplines) {
                currentRowDis++;
                tableDis->setItem(currentRowDis, 0, new QTableWidgetItem(QString::number(i->ID)));
                tableDis->setItem(currentRowDis, 1, new QTableWidgetItem(i->name));
            }
            finddis = QString();
        }
        y = 0;
        table->setGeometry(0, y, this->geometry().width(), this->geometry().height());
        tableDis->setGeometry(0, y, this->geometry().width(), this->geometry().height());
        findStat->hide();
        ui->findText->setPlainText(QString());
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
        table->setEnabled(false);
        tableDis->setEnabled(false);
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
    if (switchTable->text() == "Disciplines") {
        findstats = ui->findText->toPlainText();
        int i = 0;
        table->setRowCount(0);
        table->setRowCount(100);
        currentRow = -1;
        foreach (Statement *i, sbase->statements) {
            if (sbase->line(i).contains(findstats)) {
                currentRow++;
                table->setItem(currentRow, 0, new QTableWidgetItem(QString::number(i->ID)));
                table->setItem(currentRow, 1, new QTableWidgetItem(i->discipline->name));
                table->setItem(currentRow, 2, new QTableWidgetItem(QString::number(i->sem)));
                table->setItem(currentRow, 3, new QTableWidgetItem(i->type));
                table->setItem(currentRow, 4, new QTableWidgetItem(i->group));
                table->setItem(currentRow, 5, new QTableWidgetItem(i->number));
                table->setItem(currentRow, 6, new QTableWidgetItem(i->date));
                table->setItem(currentRow, 7, new QTableWidgetItem(i->date2));
                table->setItem(currentRow, 8, new QTableWidgetItem(i->owner));

                sfile->addStatement(i->ID, i->discipline, i->sem, i->type, i->group, i->number, i->date, i->date2, i->owner);
            }
        }
    }
    else {
        finddis = ui->findText->toPlainText();
        int i = 0;
        tableDis->setRowCount(0);
        tableDis->setRowCount(100);
        currentRowDis = -1;
        foreach (Discipline *i, dbase->disciplines) {
            if (dbase->line(i).contains(finddis)) {
                currentRowDis++;
                tableDis->setItem(currentRowDis, 0, new QTableWidgetItem(QString::number(i->ID)));
                tableDis->setItem(currentRowDis, 1, new QTableWidgetItem(i->name));

                dfile->addDiscipline(i->ID, i->name);
            }
        }
    }
}

void MainWindow::on_findText_textChanged()
{
    findStat->findChild<QPlainTextEdit*>("findText")->setStyleSheet("background-color: rgb(255, 255, 255);");
    if (switchTable->text() == "Disciplines") {findstats = ui->findText->toPlainText();}
    if (switchTable->text() == "Statements") {finddis = ui->findText->toPlainText();}
}

void MainWindow::on_resultsViev_valueChanged(int value) {}

