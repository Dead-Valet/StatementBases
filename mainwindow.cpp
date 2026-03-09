#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScrollBar>

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    table->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    stat->setGeometry(this->geometry().width() / 2 - stat->geometry().width() / 2, this->geometry().height() / 2 - stat->geometry().height() / 2, stat->geometry().width(), stat->geometry().height());
}

// MENU ACTIONS

void MainWindow::saveAct() {}

void MainWindow::loadAct() {}

void MainWindow::addDAct() {}

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

void MainWindow::EdisStatement(int id) {}
void MainWindow::EditDiscipline(int id) {}

void MainWindow::RemoveStatement() {}
void MainWindow::RemoveDiscipline() {}

void MainWindow::CheckAndDone() {

    bool allCorrect = true;

    foreach (QPlainTextEdit *i, stat->findChildren<QPlainTextEdit*>()) {
        if (i->property("Correct") == false) {
            allCorrect = false;
            break;
        }
    }

    if (allCorrect) {
        if (mode == "Add") {}
        if (mode == "Edit") {}
    }
    else {}

}

void MainWindow::on_workSpace_cellClicked(int row, int column)
{
    std::cout << "clicked" << std::endl;
}

void MainWindow::on_CancelAdding_clicked()
{
    stat->lower();
    stat->setEnabled(false);
    stat->hide();

    table->raise();
    table->setEnabled(true);
    mode = "None";
}

bool MainWindow::Check(int number, QString data) {
    if (number == 1) {}
    if (number == 2) {}
    if (number == 3) {}
    if (number == 4) {}
    if (number == 5) {}
    if (number == 6) {}
    if (number == 7) {}
    return false;
}


