#include "clipboardmonitor.h"
#include "mainwindow.h"
#include "QGuiApplication"
#include "QMimeData"

ClipboardMonitor::ClipboardMonitor(QObject *parent) : QObject(parent)
{
    clipboard = QGuiApplication::clipboard();
    startListening();
}

void ClipboardMonitor::clipboardDataChanged()
{
    if (clipboard->mimeData()->hasText()) {
        QString text = clipboard->mimeData()->text();
        emit clipboardChanged(text);
    }
}

void ClipboardMonitor::startListening() {
    connect(clipboard, &QClipboard::dataChanged, this, &ClipboardMonitor::clipboardDataChanged);
}


void ClipboardMonitor::stopListening() {
    disconnect(clipboard, &QClipboard::dataChanged, this, &ClipboardMonitor::clipboardDataChanged);
}
