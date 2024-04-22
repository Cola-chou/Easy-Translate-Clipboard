// trayicon.h
#ifndef TRAYICON_H
#define TRAYICON_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include "contextmenumanager.h"

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(ContextMenuManager *contextMenuManager,QObject* parent = nullptr);
    void showTrayIcon();
    void setflags(bool);

signals:
    void listen_clipboard_toggled(bool);
    void open_floatingBall_toggled(bool);
    void show_window();
    void close_window();
    void hide_window();
    void open_setting();

public slots:
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onListenClipboardToggled(bool);
    void onFloatingBallToggled(bool);
    void onShowWindow();
    void onCloseWindow();
    void onSettings();
private:
    QSystemTrayIcon* __trayIcon;
    ContextMenuManager *__contextMenuManager;       // 右键菜单管理器
    QMenu* __trayMenu;
    QAction* __actShowWindow;
    QAction* __actListenClipboard;
    QAction* __actExit;
    QAction* __actSettings;
    QAction* __actFloatingBall;
    bool  flags;
};

#endif // TRAYICON_H
