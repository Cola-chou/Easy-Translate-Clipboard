#pragma once

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>

class Network : public QObject {
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);
    void net_translate(const QString& text, int from, int to);

signals:
    // 成功翻译的信号
    void net_translate_finished(const QString& text, int network_status);
private:
    QString net_translate_impl(const QByteArray& resp);

public:
    enum {
        NETWORK_SUCCESS,
        NETWORK_ERROR
    };
private:
    QNetworkAccessManager* __networkManager;
    QString __url;
};
