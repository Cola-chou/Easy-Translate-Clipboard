#include "Network.h"
#include "Translation.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>

Network::Network(QObject* parent) {
    __networkManager = new QNetworkAccessManager(this);
    __url = QString("https://translate.googleapis.com/translate_a/single");
}

void Network::net_translate(const QString& text, int from, int to) {
    QUrlQuery query;
    query.addQueryItem("client", "gtx");
    query.addQueryItem("sl", "auto");

    switch (from) {
    case Translation::ZH_CN:
        query.addQueryItem("tl", "zh-CN");
        break;
    case Translation::EN_US:
        query.addQueryItem("tl", "en");
        break;
    default: break;
    }
    query.addQueryItem("dt", "t");
    query.addQueryItem("q", text);

    QUrl url(__url);
    url.setQuery(query);

    // ����ͨ��
    QNetworkRequest request(url);
    QNetworkReply* reply = __networkManager->get(request);
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();

            QString translatedText = net_translate_impl(data);
            
            emit net_translate_finished(translatedText, NETWORK_SUCCESS);
        }
        else {
            emit net_translate_finished(reply->errorString(), NETWORK_ERROR);
        }
        reply->deleteLater();
    });
    
}

QString Network::net_translate_impl(const QByteArray& resp) {

    // ���� JSON ��Ӧ
    QJsonDocument doc = QJsonDocument::fromJson(resp);

    // �����Ӧ�Ƿ���һ������
    if (doc.isArray()) {
        QJsonArray array = doc.array();

        // ��������Ƿ�Ϊ�գ��Լ���һ��Ԫ���Ƿ���һ������
        if (!array.isEmpty() && array.at(0).isArray()) {
            QJsonArray translations = array.at(0).toArray();

            // ��鷭�������Ƿ�Ϊ�գ��Լ�ÿ�������Ƿ���һ������
            if (!translations.isEmpty() && translations.at(0).isArray()) {
                QString translatedText;

                // �����������飬��ȡÿ�������ı�
                for (const QJsonValue& value : translations) {
                    QJsonArray translation = value.toArray();

                    // ��鷭�������Ƿ�����㹻��Ԫ�أ����ҵ�һ��Ԫ�����ַ�������
                    if (translation.size() >= 2 && translation.at(0).isString()) {
                        // �������ı���ӵ�����ַ�����
                        translatedText.append(translation.at(0).toString());
                    }
                }

                // ������ȡ�ķ����ı�
                return translatedText;
            }
        }
    }

    // �������ʧ�ܣ����ؿ��ַ���
    return QString();
}
