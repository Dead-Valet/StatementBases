#ifndef XMLSAVER_H
#define XMLSAVER_H

#include "disfiles.h"
#include "statfiles.h"
#include "mainwindow.h"

class MainWindow;

class xmlSaver
{
public:
    xmlSaver(QString filename, MainWindow *win);
    QString file;
    MainWindow *w;
    void save(statFiles *file);
    void save(disFiles *file);
};

#endif // XMLSAVER_H
