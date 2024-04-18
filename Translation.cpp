#include "Translation.h"
#include <QString>
Translation::Translation(QObject* parent) : QObject(parent) {
    __lsrc = { QString::fromLocal8Bit("ÖÐÎÄ"), ZH_CN };
    __ldest = { "English", EN_US };

    __clipboardMonitor = new ClipboardMonitor(this);
    __network = new Network(this);


    connect(__network, &Network::net_translate_finished, this, &Translation::net_translation_finished);
    connect(__network, &Network::net_translate_error, this, &Translation::net_translation_error);
    connect(__clipboardMonitor, &ClipboardMonitor::clipboardChanged, this, &Translation::translation);
    connect(__clipboardMonitor, &ClipboardMonitor::clipboardChanged, this, &Translation::clipboard_exist_data);
}

void Translation::initComboBox(QComboBox* box, int index) const {
    qDebug() << __lsrc.name;
    box->addItem(__lsrc.name, __lsrc.code);
    box->addItem(__ldest.name, __ldest.code);
    box->setCurrentIndex(index);
}

void Translation::translation(const QString& text) {
    __network->net_translate(text, __lsrc.code, __ldest.code);
}

void Translation::net_translation_error(const QString& text) {
    emit translation_error(text);
}

void Translation::net_translation_finished(const QString& text) {
    emit translation_finished(text);
}

void Translation::clipboard_exist_data(const QString& text) {
    emit clipboard_data(text);
}


void Translation::listen_clipboard_toggled(bool opt) {
    __clipboardMonitor->listening(opt);
}