#include "diswindow.h"
#include "ui_diswindow.h"

diswindow::diswindow(QWidget *parent, MainWindow *win)
    : QMainWindow(parent), w(win)
    , ui(new Ui::diswindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString());
    ui->deleteButton_2->hide();

}

void diswindow::switchText(QString text, bool hided) {
    ui->label_18->setText(text);
    if (hided) {
        ui->deleteButton_2->hide();
    }
    else {
        ui->deleteButton_2->show();
        ui->plainTextEdit_9->setPlainText(w->tableDis->item(w->editedRow, 1)->text());
    }
}

void diswindow::on_deleteButton_2_clicked() {
    QMessageBox ms;
    ms.setWindowTitle("Внимание!");
    ms.setText("Вы уверены, что хотите удалить дисциплину?");
    QPushButton *yes = ms.addButton(QString("Да"), QMessageBox::AcceptRole);
    ms.addButton(QString("Нет"), QMessageBox::RejectRole);
    ms.setIcon(QMessageBox::Question);
    ms.exec();
    if (ms.clickedButton() == yes) {
        RemoveDiscipline(w->editedRow);
        w->table->setEnabled(true);
        w->tableDis->setEnabled(true);
    }
}

void diswindow::RemoveDiscipline(int row) {
    foreach (Discipline *i, w->disciplines) {
        if (i->ID == w->editedId) {

            foreach (Statement *j, w->sfile->statements) {
                if (j->discipline->ID == i->ID) {
                    QMessageBox ms;
                    ms.setWindowTitle(QString());
                    ms.setText("Невозможно удалить, есть ведомости, содеражащие эту дисциплину");
                    ms.exec();
                    return;
                }
            }
            w->disciplines.remove(w->disciplines.indexOf(i));
            w->tableDis->removeRow(row);
            w->currentRowDis--;
            w->dfile->removeDiscipline(w->editedId);

            ui->deleteButton_2->hide();

            ui->plainTextEdit_9->clear();
            ui->plainTextEdit_9->setProperty("Correct", false);
            ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");

            w->table->setEnabled(true);
            w->tableDis->setEnabled(true);

            mode = "None";
            w->mode = "None";
            this->hide();

            return;
        }
    }
}


bool diswindow::CheckAndDoneDis()
{
    if (ui->plainTextEdit_9->property("Correct") == true) {

        w->unlockMenu();

        QString name = ui->plainTextEdit_9->toPlainText().simplified();

        if (mode == "Add")
        {
            w->currentRowDis++;

            w->disciplines.append(new Discipline(w->lD + 1, name));
            w->dfile->addDiscipline(w->lD + 1, name);
            w->lD ++;

            w->tableDis->setItem(w->currentRowDis, 0, new QTableWidgetItem(QString::number(w->disciplines.last()->ID)));
            w->tableDis->setItem(w->currentRowDis, 1, new QTableWidgetItem(name));

            return true;
        }
        if (mode == "Edit") {
            foreach (Discipline *i, w->disciplines) {
                if (i->ID == w->editedId) {

                    i->name = name;
                    w->dfile->editDiscipline(w->editedId, name);
                    w->tableDis->setItem(w->editedRow, 1, new QTableWidgetItem(name));
                    w->editedRow = 0;
                    w->editedId = 0;
                    return true;
                }
            }
        }
    }
    std::cout << "incorrect data format for discipline" << std::endl;
    return false;
}

void diswindow::on_ConfirmAdding_2_clicked()
{
    if (CheckAndDoneDis())
    {
        ui->plainTextEdit_9->clear();
        ui->plainTextEdit_9->setProperty("Correct", false);
        ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");

        w->tableDis->setEnabled(true);
        w->table->setEnabled(true);
        mode = "None";
        w->mode = "None";

        this->hide();
    }
}


void diswindow::on_CancelAdding_2_clicked()
{
    ui->plainTextEdit_9->clear();
    ui->plainTextEdit_9->setProperty("Correct", false);
    ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");

    w->table->setEnabled(true);
    w->tableDis->setEnabled(true);

    mode = "None";
    w->mode = "None";
    w->editedRow = 0;
    w->editedId = 0;

    ui->deleteButton_2->hide();
    w->unlockMenu();
    this->hide();
}

void diswindow::on_plainTextEdit_9_textChanged()
{

    QString data = ui->plainTextEdit_9->toPlainText();
    if (data.isEmpty()) {
        ui->plainTextEdit_9->setProperty("Correct", false);
        ui->plainTextEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);");
        return;
    }

    if (QRegularExpression("^(\\s)*[А-ЯЁ]([а-яА-ЯёЁ])+(\\s+(([а-яА-ЯёЁ])+|\\d+))*(\\s)*$").match(data).hasMatch()) {
        foreach (Discipline *i, w->disciplines) {
            if (i->name == data.simplified() && (i->ID != w->editedId)) {
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

void diswindow::closeEvent(QCloseEvent *event)
{
    w->mode = "None";
    mode = "None";
    w->table->setEnabled(true);
    w->tableDis->setEnabled(true);
    w->editedRow = 0;
    w->editedId = 0;
    w->unlockMenu();
}

