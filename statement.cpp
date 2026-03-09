#include "statement.h"

Statement::Statement(int _ID, Discipline *_discipline, int _sem, QString _type, QString _group, QDate _date, QDate _date2, QString _owner) : ID(_ID),
    discipline(_discipline), sem(_sem), type(_type), group(_group), date(_date), date2(_date2), owner(_owner) {}
