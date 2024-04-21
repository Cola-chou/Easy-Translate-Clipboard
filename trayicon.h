// trayicon.h
#ifndef TRAYICON_H
#define TRAYICON_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject* parent = nullptr);
    void showTrayIcon();
    void setflags(bool);

signals:
    void listen_clipboard_toggled(bool);
    void show_window();
    void close_window();
    void hide_window();

public slots:
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onListenClipboardToggled(bool);
    void onShowWindow();
    void onCloseWindow();
private:
    QSystemTrayIcon* __trayIcon;
    QMenu* __trayMenu;
    QAction* __actShowWindow;
    QAction* __actListenClipboard;
    QAction* __actExit;
    bool  flags;
};

#endif // TRAYICON_H
