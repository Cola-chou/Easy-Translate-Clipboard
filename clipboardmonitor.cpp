#include "clipboardmonitor.h"
#include "mainwindow.h"
#include "QGuiApplication"
#include "QMimeData"

ClipboardMonitor::ClipboardMonitor(QObject* parent) : QObject(parent)
{
    clipboard = QGuiApplication::clipboard();
    listening(true);
}

void ClipboardMonitor::clipboardDataChanged()
{
    if (clipboard->mimeData()->hasText()) {
        QString text = clipboard->mimeData()->text();
        emit clipboard_changed(text);
    }
}

void ClipboardMonitor::listening(bool opt) {
    if (opt)
        connect(clipboard, &QClipboard::dataChanged, this, &ClipboardMonitor::clipboardDataChanged);
    else
        disconnect(clipboard, &QClipboard::dataChanged, this, &ClipboardMonitor::clipboardDataChanged);

}


