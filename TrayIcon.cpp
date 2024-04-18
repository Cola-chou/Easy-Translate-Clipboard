// trayicon.cpp
#include "TrayIcon.h"
#include <QDebug>

TrayIcon::TrayIcon(QObject*parent) : QObject(parent)
{
    flags = false;
    // 新建QSystemTrayIcon对象
    __trayIcon = new QSystemTrayIcon(this);
    // 创建菜单事件
    __actShowWindow = new QAction("打开主界面", this);
    __actListenClipboard = new QAction("监听剪贴板", this);
    __actSettings = new QAction("设置", this);
    //__actListenClipboard->setCheckable(true);
    //__actListenClipboard->setChecked(true);
    __actExit = new QAction("退出", this);
    // 创建菜单
    __trayMenu = new QMenu(nullptr);
    // 新增一个菜单
    __trayMenu->addAction(__actShowWindow);
    __trayMenu->addAction(__actSettings);
    // 增加分割符
    __trayMenu->addSeparator();
    // 新增一个菜单
    __trayMenu->addAction(__actExit);
    // 给托盘加入菜单
    __trayIcon->setContextMenu(__trayMenu);

    connect(__trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::onTrayIconActivated);
    connect(__actShowWindow, &QAction::triggered,this, &TrayIcon::onShowWindow);
    connect(__actExit, &QAction::triggered,this, &TrayIcon::onCloseWindow);
    connect(__actListenClipboard, &QAction::toggled, this, &TrayIcon::onListenClipboardToggled);
    connect(__actSettings, &QAction::triggered, this, &TrayIcon::onSettings);
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

void TrayIcon::onListenClipboardToggled(bool opt) {
    emit listen_clipboard_toggled(opt);
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
