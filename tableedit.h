#ifndef TABLEEDIT_H
#define TABLEEDIT_H
#include <QTableWidget>
#include "statement.h"
#include "discipline.h"
#include <QList>

void TableEditg(QTableWidgetItem field, QList<Statement> statements);
void TableEditg(QTableWidgetItem field, QList<Discipline> disciplines);

#endif // TABLEEDIT_H
