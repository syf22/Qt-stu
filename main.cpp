#include "mainwindow.h"

#include <QApplication>
#include"stusql.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    stusql sql;


    return a.exec();
}
