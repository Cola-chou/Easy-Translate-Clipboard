// trayicon.cpp
#include "trayicon.h"
#include "QApplication"
#include "QtDebug"

TrayIcon::TrayIcon(QMainWindow *mainWindow,QObject *parent) : QObject(parent)
{
    this->mainWindow = mainWindow;
    trayIcon = new QSystemTrayIcon(QIcon(":/images/icons/aa.ico"));
    trayMenu = new QMenu;

    QAction *quitAction = trayMenu->addAction("Quit");
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::showMainWindow);

//    // 连接托盘图标的点击信号与自定义信号
//    connect(trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
//        if (reason == QSystemTrayIcon::Trigger) {
//            emit trayIconClicked();
//        }
//    });
}

void TrayIcon::showMainWindow()
{
//    this->mainWindow->show();
    emit trayIconClicked();
    qDebug()<<"点击了托盘图标";
}
