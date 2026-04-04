#ifndef XMLSAVER_H
#define XMLSAVER_H

#include "disfiles.h"
#include "statfiles.h"
#include "mainwindow.h"

class MainWindow;
class statFiles;
class disFiles;

class xmlSaver
{
public:
    xmlSaver(QString _filename, MainWindow *win);
    QString filename;
    MainWindow *w;
    void save(statFiles *file);
    void save(disFiles *file);
    void load(statFiles *file);
    void load(disFiles *file);

};

#endif // XMLSAVER_H
