#pragma once

#include <QObject>
#include "clipboardmonitor.h"
#include "Network.h"
#include <QComboBox>

class MainWindow;

class Translation : public QObject {
    Q_OBJECT

        friend class MainWindow;
public:
    explicit Translation(QObject* parent = nullptr);
    void initComboBox(QComboBox*, int) const;

public slots:
    void translation(const QString& text);
    void net_translation_error(const QString& text);
    void net_translation_finished(const QString& text);
    void listen_clipboard_toggled(bool);    
    void clipboard_exist_data(const QString& text);

signals:
    void translation_finished(const QString& text);
    void translation_error(const QString& text);
    void clipboard_data(const QString& text);

public:
    enum {
        ZH_CN,
        EN_US
    };
private:
    struct Language {
        QString name;
        int code;
    }__lsrc, __ldest;

    ClipboardMonitor* __clipboardMonitor;
    Network* __network;
};
