// trayicon.h
#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include "QMainWindow"

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QMainWindow *mainWindow,QObject *parent = nullptr);

signals:
    void trayIconClicked();

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QMainWindow *mainWindow;


public slots:
    void showMainWindow();
};

#endif // TRAYICON_H
