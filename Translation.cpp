#include "Translation.h"
#include <QString>

Translation::Translation(QObject* parent) : QObject(parent)
{
    __clipboardMonitor = new ClipboardMonitor(this);
    __network = new Network(this);
    initLangMap();

    connect(__network, &Network::net_translate_finished, this, &Translation::net_translation_finished);
    connect(__clipboardMonitor, &ClipboardMonitor::clipboardChanged, this, &Translation::translation);
    connect(__clipboardMonitor, &ClipboardMonitor::clipboardChanged, this, &Translation::clipboard_exist_data);
}

void Translation::initComboBox(QComboBox* box, int index) const
{
    box->addItem(__lsrc.name, __lsrc.code);
    box->addItem(__ldest.name, __ldest.code);
    box->setCurrentIndex(index);
}

void Translation::translation(const QString& text)
{
    __network->net_translate(text, __lsrc.code, __ldest.code);
}

void Translation::net_translation_finished(const QString& text, int netstatus)
{
    emit translation_finished(text);
}

void Translation::clipboard_exist_data(const QString& text)
{
    emit clipboard_data(text);
}


void Translation::listen_clipboard_toggled(bool opt)
{
    __clipboardMonitor->listening(opt);
}

void Translation::initLangMap()
{
    __langmap.insert(ZH_CN, {QString::fromLocal8Bit("ÖÐÎÄ"), ZH_CN});
    __langmap.insert(EN_US, { QString::fromLocal8Bit("Ó¢Óï(US)"), EN_US});
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

