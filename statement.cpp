#include "statement.h"

Statement::Statement(int _ID, QString _discipline, int _sem, QString _type, QString _group, QString _number, QString _date, QString _date2, QString _owner) : ID(_ID),
    discipline(_discipline), sem(_sem), type(_type), group(_group), number(_number), date(_date), date2(_date2), owner(_owner) {}
Statement::~Statement() {}
