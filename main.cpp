#include "mainwindow.h"
#include "trayicon.h"
#include <QCoreApplication>
#include <QSslConfiguration>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("EasyTranslateClipboard");
    QApplication::setApplicationName("clipboard");

    MainWindow w;

    return a.exec();
}
