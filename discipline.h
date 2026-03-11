#ifndef DISCIPLINE_H
#define DISCIPLINE_H
#include <QString>

class Discipline
{
public:
    Discipline(QString _name, int _id);
    QString name;
    int ID;
    ~Discipline();
};

#endif // DISCIPLINE_H
