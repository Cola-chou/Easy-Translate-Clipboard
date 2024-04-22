// contextmenumanager.cpp
#include "contextmenumanager.h"
#include <QDebug>

ContextMenuManager::ContextMenuManager(QObject *parent) : QObject(parent)
{
    m_menu = new QMenu(nullptr);

    m_actShowWindow = m_menu->addAction("打开主界面");
    m_actListenClipboard = m_menu->addAction("监听剪贴板");
    m_actSettings = m_menu->addAction("设置");
    m_actFloatingBall = m_menu->addAction("悬浮球");
    m_actFloatingBall->setCheckable(true);
    m_actFloatingBall->setChecked(true);
    m_actExit = m_menu->addAction("退出");

    connect(m_actShowWindow, &QAction::triggered, this, &ContextMenuManager::onShowWindowTriggered);
    connect(m_actListenClipboard, &QAction::toggled, this, &ContextMenuManager::onListenClipboardToggled);
    connect(m_actSettings, &QAction::triggered, this, &ContextMenuManager::onOpenSettingsTriggered);
    connect(m_actFloatingBall, &QAction::toggled, this, &ContextMenuManager::onToggleFloatingBallToggled);
    connect(m_actExit, &QAction::triggered, this, &ContextMenuManager::onQuitApplicationTriggered);
}

QMenu* ContextMenuManager::getMenu()
{
    return m_menu;
}

void ContextMenuManager::onShowWindowTriggered()
{
    emit showWindow();
}

void ContextMenuManager::onCloseWindowTriggered()
{
    emit closeWindow();
}

void ContextMenuManager::onListenClipboardToggled(bool opt)
{
    emit listenClipboard(opt);
}

void ContextMenuManager::onOpenSettingsTriggered()
{
    emit openSettings();
}

void ContextMenuManager::onToggleFloatingBallToggled(bool opt)
{
    emit toggleFloatingBall(opt);
}

void ContextMenuManager::onQuitApplicationTriggered()
{
    emit quitApplication();
}
