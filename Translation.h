#pragma once

#include <QObject>
#include "clipboardmonitor.h"
#include "Network.h"
#include <QComboBox>

class MainWindow;

class Translation : public QObject {
    Q_OBJECT
public:
    explicit Translation(QObject* parent = nullptr);
    void initComboBox(QComboBox*, int) const;

public slots:
    void translation(const QString& text);
    void netTranslationFinished(const QString& text, int netstatus);
    void listenClipboardToggled(bool);    
    void clipboardExistData(const QString& text);
    void swapLanage(const QString& text);

signals:
    void translation_finished(const QString& text);
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
    };
    QMap<int, Language> __langmap;
    void initLangMap();

private:
    Language __lsrc, __ldest;
    ClipboardMonitor* __clipboardMonitor;
    Network* __network;
};
