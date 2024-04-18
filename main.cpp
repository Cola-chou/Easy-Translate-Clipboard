#include "mainwindow.h"
#include "trayicon.h"
#include <QCoreApplication>
#include <QSslConfiguration>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    return a.exec();
}
