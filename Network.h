#pragma once

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>

class Network : public QObject {
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);

public:
    void net_translate(const QString& text, int from, int to);

signals:
    void net_translate_finished(const QString& text);
    void net_translate_error(const QString& text);
private:
    QString net_translate_impl(const QByteArray& resp);
private:
    QNetworkAccessManager* __networkManager;
    QString __url;
};
