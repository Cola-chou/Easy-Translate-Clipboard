// trayicon.cpp
#include "trayicon.h"
#include <QDebug>

TrayIcon::TrayIcon(ContextMenuManager *contextMenuManager,QObject*parent) : QObject(parent)
{
    flags = false;
    // 新建QSystemTrayIcon对象
    __trayIcon = new QSystemTrayIcon(this);
    // 从右键菜单管理器中获取创建好的右键菜单
    __contextMenuManager = contextMenuManager;
    __trayMenu = __contextMenuManager->getMenu();
    __trayIcon->setContextMenu(__trayMenu);
    // 连接右键菜单管理器中的信号
    connect(__trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::onTrayIconActivated);
    connect(__contextMenuManager, &ContextMenuManager::showWindow,this, &TrayIcon::onShowWindow);
    connect(__contextMenuManager, &ContextMenuManager::closeWindow,this, &TrayIcon::onCloseWindow);
    connect(__contextMenuManager, &ContextMenuManager::listenClipboard, this, &TrayIcon::onListenClipboardToggled);
    connect(__contextMenuManager,&ContextMenuManager::toggleFloatingBall,this,&TrayIcon::onFloatingBallToggled);
    connect(__contextMenuManager, &ContextMenuManager::openSettings, this, &TrayIcon::onSettings);
}

void TrayIcon::showTrayIcon() {
    // 新建托盘要显示的icon
    QIcon icon = QIcon(":/images/icons/aa.ico");
    // 设置托盘icon
    __trayIcon->setIcon(icon);
    // 设置托盘鼠标悬浮显示内容
    __trayIcon->setToolTip("翻译");
    __trayIcon->show();
}

void TrayIcon::onTrayIconActivated(QSystemTrayIcon::ActivationReason action) {
    switch (action) {
    case QSystemTrayIcon::Unknown:
        qDebug() << "未知事件";
        break;
    case QSystemTrayIcon::Context:
        qDebug() << "右键点击了图标(请求托盘上下文)";
        break;
    case QSystemTrayIcon::Trigger:
        qDebug() << "单机了图标";
        break;
    case QSystemTrayIcon::DoubleClick:
        if (flags) {
            flags = !flags;
            emit hide_window();
        }
        else {
            flags = !flags;
            emit show_window();
        }
        break;
    case QSystemTrayIcon::MiddleClick:
        qDebug() << "鼠标中间点击了图标";
        break;
    }
}


void TrayIcon::onFloatingBallToggled(bool opt)
{
    emit open_floatingBall_toggled(opt);
}

void TrayIcon::onShowWindow() {
    flags = true;
    emit show_window();
}

void TrayIcon::onCloseWindow() {
    emit close_window();
}

void TrayIcon::onSettings()
{
    emit open_setting();
}


void TrayIcon::setflags(bool f)
{
    flags = f;
}
