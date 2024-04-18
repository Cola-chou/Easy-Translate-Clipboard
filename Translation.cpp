#include "Translation.h"
#include <QString>

Translation::Translation(QObject* parent) : QObject(parent)
{
    __clipboardMonitor = new ClipboardMonitor(this);
    __network = new Network(this);
    initLangMap();

    connect(__network, &Network::net_translate_finished, this, &Translation::netTranslationFinished);
    connect(__clipboardMonitor, &ClipboardMonitor::clipboard_changed, this, &Translation::translation);
    connect(__clipboardMonitor, &ClipboardMonitor::clipboard_changed, this, &Translation::clipboardExistData);
}

void Translation::initComboBox(QComboBox* box, int index) const
{
    box->addItem(__lsrc.name, __lsrc.code);
    box->addItem(__ldest.name, __ldest.code);
    box->setCurrentIndex(index);
}

void Translation::translation(const QString& text)
{
    __network->netTranslate(text, __lsrc.code, __ldest.code);
}

void Translation::netTranslationFinished(const QString& text, int netstatus)
{
    emit translation_finished(text);
}

void Translation::clipboardExistData(const QString& text)
{
    emit clipboard_data(text);
}


void Translation::listenClipboardToggled(bool opt)
{
    __clipboardMonitor->listening(opt);
}

void Translation::initLangMap()
{
    __langmap.insert(ZH_CN, {u8"中文", ZH_CN});
    __langmap.insert(EN_US, { u8"英语(US)", EN_US});
    __lsrc = __langmap.value(Translation::ZH_CN);
    __ldest = __langmap.value(Translation::EN_US);
}

void Translation::swapLanage(const QString& text)
{
    auto tmp = __lsrc;
    __lsrc = __ldest;
    __ldest = tmp;
    emit translation(text);
}

