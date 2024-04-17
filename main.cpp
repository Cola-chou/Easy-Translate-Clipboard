#include "mainwindow.h"
#include "trayicon.h"
#include <QCoreApplication>
#include <QSslConfiguration>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

//    // 创建托盘图标
//    TrayIcon trayIcon(&w);


//    // 当托盘图标被点击时，显示主窗口
//      QObject::connect(&trayIcon, &TrayIcon::trayIconClicked, &w, &MainWindow::show);
    return a.exec();
}
