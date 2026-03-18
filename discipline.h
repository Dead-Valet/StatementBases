#ifndef DISCIPLINE_H
#define DISCIPLINE_H
#include <QString>

class Discipline
{
public:
    Discipline(int _id, QString _name);
    QString name;
    int ID;
    ~Discipline();
};

#endif // DISCIPLINE_H
