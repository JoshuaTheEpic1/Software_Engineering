#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.test();
    w.CreateLists();
    w.show();
    return a.exec();

}
