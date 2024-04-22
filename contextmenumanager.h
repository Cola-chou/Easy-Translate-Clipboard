// contextmenumanager.h
#ifndef CONTEXTMENUMANAGER_H
#define CONTEXTMENUMANAGER_H

#include <QObject>
#include <QMenu>
#include <QAction>

class ContextMenuManager : public QObject
{
    Q_OBJECT
public:
    explicit ContextMenuManager(QObject *parent = nullptr);
    QMenu* getMenu();

signals:
    void showWindow();
    void closeWindow();
    void listenClipboard(bool opt);
    void openSettings();
    void toggleFloatingBall(bool opt);
    void quitApplication();

private slots:
    void onShowWindowTriggered();
    void onCloseWindowTriggered();
    void onListenClipboardToggled(bool opt);
    void onOpenSettingsTriggered();
    void onToggleFloatingBallToggled(bool opt);
    void onQuitApplicationTriggered();

private:
    QMenu* m_menu;
    QAction* m_actShowWindow;
    QAction* m_actListenClipboard;
    QAction* m_actSettings;
    QAction* m_actFloatingBall;
    QAction* m_actExit;
};

#endif // CONTEXTMENUMANAGER_H
