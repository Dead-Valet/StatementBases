#include "statwindow.h"
#include "./ui_statwindow.h"

StatWindow::StatWindow(QWidget *parent, MainWindow *win)
    : QMainWindow{parent}, ui(new Ui::StatWindow), w(win)
{
    ui->setupUi(this);
    ui->deleteButton->hide();
    this->setWindowTitle(QString());

}

void StatWindow::switchText(QString text, bool hided) {
    ui->label_9->setText(text);
    if (hided) {
        ui->deleteButton->hide();
        ui->ConfirmAdding->setText("Добавить");
    }
    else {
        ui->deleteButton->show();
        ui->ConfirmAdding->setText("Сохранить");

        ui->plainTextEdit->setPlainText(w->table->item(w->editedRow, 1)->text());
        ui->plainTextEdit_2->setPlainText(w->table->item(w->editedRow, 2)->text());
        ui->plainTextEdit_3->setPlainText(w->table->item(w->editedRow, 3)->text());
        ui->plainTextEdit_4->setPlainText(w->table->item(w->editedRow, 4)->text());
        ui->plainTextEdit_5->setPlainText(w->table->item(w->editedRow, 5)->text());
        ui->plainTextEdit_6->setPlainText(w->table->item(w->editedRow, 6)->text());
        ui->plainTextEdit_7->setPlainText(w->table->item(w->editedRow, 7)->text());
        ui->plainTextEdit_8->setPlainText(w->table->item(w->editedRow, 8)->text());
    }
}

void StatWindow::on_deleteButton_clicked() {
    QMessageBox ms;
    ms.setWindowTitle("Внимание!");
    ms.setText("Вы уверены, что хотите удалить ведомость?");
    QPushButton *yes = ms.addButton(QString("Да"), QMessageBox::AcceptRole);
    ms.addButton(QString("Нет"), QMessageBox::RejectRole);
    ms.setIcon(QMessageBox::Question);
    ms.exec();
    if (ms.clickedButton() == yes) {
        RemoveStatement(w->editedRow);
    }
}

void StatWindow::RemoveStatement(int row) {
    foreach (Statement *i, w->statements) {
        if (i->ID == w->editedId) {

            w->statements.remove(w->statements.indexOf(i));
            w->sfile->removeStatement(w->editedId);
            w->sbase->removeStatement(w->editedId);
            w->table->removeRow(row);
            w->currentRow--;

            this->hide();
            foreach (QPlainTextEdit *i, findChildren<QPlainTextEdit*>()) {
                i->clear();
                i->setProperty("Correct", false);
                i->setStyleSheet("background-color: rgb(255, 255, 255);");
            }
            w->editedId = 0;
            w->editedRow = 0;

            w->table->setEnabled(true);
            w->tableDis->setEnabled(true);

            mode = "None";
            w->mode = "None";
            w->unlockMenu();
        }
    }
}

bool StatWindow::CheckAndDone()
{
    bool allCorrect = true;

    foreach (QPlainTextEdit *i, this->findChildren<QPlainTextEdit*>()) {
        if (i->property("Correct") == false) {
            allCorrect = false;
            break;
        }
    }

    if (allCorrect) {

        w->unlockMenu();

        QList<QPlainTextEdit*> data = findChildren<QPlainTextEdit*>();

        Discipline *discipline;
        foreach (Discipline *i, w->dbase->disciplines) {
            if (i->name == data[0]->toPlainText().simplified()) {
                discipline = i;
                break;
            }
        }
        int sem = data[1]->toPlainText().toInt();
        QString type = data[2]->toPlainText().simplified();
        QString group = data[3]->toPlainText().simplified();
        QString number = data[4]->toPlainText().simplified();
        QString date = data[6]->toPlainText().simplified();
        QString date2 = data[5]->toPlainText().simplified();
        QString owner = data[7]->toPlainText().simplified();

        if (mode == "Add") {
            w->sbase->addStatement(0, discipline, sem, type, group, number, date, date2, owner);
            w->statements.append(new Statement(w->sbase->statements.last()->ID, discipline, sem, type, group, number, date, date2, owner));
            w->sfile->addStatement(w->sbase->statements.last()->ID, discipline, sem, type, group, number, date, date2, owner);

            w->currentRow++;
            w->table->setItem(w->currentRow, 0, new QTableWidgetItem(QString::number(w->sbase->statements.last()->ID)));
            w->table->setItem(w->currentRow, 1, new QTableWidgetItem(discipline->name));
            w->table->setItem(w->currentRow, 2, new QTableWidgetItem(QString::number(sem)));
            w->table->setItem(w->currentRow, 3, new QTableWidgetItem(type));
            w->table->setItem(w->currentRow, 4, new QTableWidgetItem(group));
            w->table->setItem(w->currentRow, 5, new QTableWidgetItem(number));
            w->table->setItem(w->currentRow, 6, new QTableWidgetItem(date));
            w->table->setItem(w->currentRow, 7, new QTableWidgetItem(date2));
            w->table->setItem(w->currentRow, 8, new QTableWidgetItem(owner));

            return true;
        }
        if (mode == "Edit") {
            foreach (Statement *i, w->statements) {
                if (i->ID == w->editedId) {

                    i->discipline = discipline;
                    i->sem = sem;
                    i->type = type;
                    i->group = group;
                    i->number = number;
                    i->date = date;
                    i->date2 = date2;
                    i->owner = owner;

                    w->table->setItem(w->editedRow, 1, new QTableWidgetItem(discipline->name));
                    w->table->setItem(w->editedRow, 2, new QTableWidgetItem(QString::number(sem)));
                    w->table->setItem(w->editedRow, 3, new QTableWidgetItem(type));
                    w->table->setItem(w->editedRow, 4, new QTableWidgetItem(group));
                    w->table->setItem(w->editedRow, 5, new QTableWidgetItem(number));
                    w->table->setItem(w->editedRow, 6, new QTableWidgetItem(date));
                    w->table->setItem(w->editedRow, 7, new QTableWidgetItem(date2));
                    w->table->setItem(w->editedRow, 8, new QTableWidgetItem(owner));

                    w->sfile->editStatement(w->editedId, discipline, sem, type, group, number, date, date2, owner);
                    w->sbase->editStatement(w->editedId, discipline, sem, type, group, number, date, date2, owner);

                    w->editedRow = 0;
                    w->editedId = 0;

                    this->findChild<QPushButton*>("deleteButton")->hide();
                    return true;
                }
            }
        }
    }

    return false;
}

void StatWindow::on_ConfirmAdding_clicked()
{
    if (CheckAndDone())
    {
        foreach (QPlainTextEdit *i, this->findChildren<QPlainTextEdit*>()) {
            i->clear();
            i->setProperty("Correct", false);
            i->setStyleSheet("background-color: rgb(255, 255, 255);");
        }

        mode = "None";
        w->mode = "None";
        w->table->setEnabled(true);
        w->tableDis->setEnabled(true);
        this->hide();
    }
}


// Discipline check

void StatWindow::on_plainTextEdit_textChanged()
{
    if (QRegularExpression("^(\\s)*[А-ЯЁ]([а-яА-ЯёЁ])+(\\s+(([а-яА-ЯёЁ])+|\\d+))*(\\s)*$").match(ui->plainTextEdit->toPlainText()).hasMatch()) {
        foreach (Discipline *i, w->dbase->disciplines) {
            if (i->name == ui->plainTextEdit->toPlainText().simplified()) {
                ui->plainTextEdit->setProperty("Correct", true);
                ui->plainTextEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
                return;
            }
        }
    }
    if (ui->plainTextEdit->toPlainText().isEmpty()) {
        ui->plainTextEdit->setProperty("Correct", false);
        ui->plainTextEdit_2->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    ui->plainTextEdit->setProperty("Correct", false);
    ui->plainTextEdit->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Sem check

void StatWindow::on_plainTextEdit_2_textChanged()
{
    std::string data = ui->plainTextEdit_2->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_2->setProperty("Correct", false);
        ui->plainTextEdit_2->setStyleSheet("background-color: rgb(255, 255, 255);");
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

void StatWindow::on_plainTextEdit_3_textChanged()
{
    std::string data = ui->plainTextEdit_3->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_3->setProperty("Correct", false);
        ui->plainTextEdit_3->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    if (types.contains(ui->plainTextEdit_3->toPlainText().simplified())) {
        ui->plainTextEdit_3->setProperty("Correct", true);
        ui->plainTextEdit_3->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }
    ui->plainTextEdit_3->setProperty("Correct", false);
    ui->plainTextEdit_3->setStyleSheet("background-color: rgb(255, 123, 123);");
}

// Group check

void StatWindow::on_plainTextEdit_4_textChanged()
{
    QString data = ui->plainTextEdit_4->toPlainText();
    if (data.isEmpty()) {
        ui->plainTextEdit_4->setProperty("Correct", false);
        ui->plainTextEdit_4->setStyleSheet("background-color: rgb(255, 255, 255);");
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

void StatWindow::on_plainTextEdit_5_textChanged()
{
    std::string data = ui->plainTextEdit_5->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_5->setProperty("Correct", false);
        ui->plainTextEdit_5->setStyleSheet("background-color: rgb(255, 255, 255);");
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

void StatWindow::on_plainTextEdit_6_textChanged()
{
    std::string data = ui->plainTextEdit_6->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_6->setProperty("Correct", false);
        ui->plainTextEdit_6->setStyleSheet("background-color: rgb(255, 255, 255);");
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

void StatWindow::on_plainTextEdit_7_textChanged()
{
    std::string data = ui->plainTextEdit_7->toPlainText().toStdString();
    if (data.empty()) {
        ui->plainTextEdit_7->setProperty("Correct", false);
        ui->plainTextEdit_7->setStyleSheet("background-color: rgb(255, 255, 255);");
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

void StatWindow::on_plainTextEdit_8_textChanged()
{
    QString data = ui->plainTextEdit_8->toPlainText();
    if (data.isEmpty()) {
        ui->plainTextEdit_8->setProperty("Correct", false);
        ui->plainTextEdit_8->setStyleSheet("background-color: rgb(255, 255, 255);");
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


void StatWindow::on_CancelAdding_clicked()
{

    foreach (QPlainTextEdit *i, this->findChildren<QPlainTextEdit*>()) {
        i->clear();
        i->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

    mode = "None";
    w->mode = "None";
    w->table->setEnabled(true);
    w->tableDis->setEnabled(true);
    w->editedRow = 0;
    w->editedId = 0;

    this->findChild<QPushButton*>("deleteButton")->hide();
    w->unlockMenu();
    this->hide();
}


void StatWindow::closeEvent(QCloseEvent *event)
{
    w->mode = "None";
    mode = "None";
    w->table->setEnabled(true);
    w->tableDis->setEnabled(true);
    w->editedRow = 0;
    w->editedId = 0;
    w->unlockMenu();

    foreach (QPlainTextEdit *i, this->findChildren<QPlainTextEdit*>()) {
        i->clear();
        i->setStyleSheet("background-color: rgb(255, 255, 255);");
    }
}

