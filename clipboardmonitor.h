// clipboardmonitor.h
#ifndef CLIPBOARDMONITOR_H
#define CLIPBOARDMONITOR_H

#include <QObject>
#include <QClipboard>

class ClipboardMonitor : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardMonitor(QObject *parent = nullptr);
    void listening(bool);
signals:
    void clipboard_changed(const QString &text);

private slots:
    void clipboardDataChanged();

private:
    QClipboard *clipboard;
};
#endif // CLIPBOARDMONITOR_H
