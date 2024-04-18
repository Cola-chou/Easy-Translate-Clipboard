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

    // 网络通信
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

    // 解析 JSON 响应
    QJsonDocument doc = QJsonDocument::fromJson(resp);

    // 检查响应是否是一个数组
    if (doc.isArray()) {
        QJsonArray array = doc.array();

        // 检查数组是否为空，以及第一个元素是否是一个数组
        if (!array.isEmpty() && array.at(0).isArray()) {
            QJsonArray translations = array.at(0).toArray();

            // 检查翻译数组是否为空，以及每个翻译是否是一个数组
            if (!translations.isEmpty() && translations.at(0).isArray()) {
                QString translatedText;

                // 遍历翻译数组，提取每个翻译文本
                for (const QJsonValue& value : translations) {
                    QJsonArray translation = value.toArray();

                    // 检查翻译数组是否包含足够的元素，并且第一个元素是字符串类型
                    if (translation.size() >= 2 && translation.at(0).isString()) {
                        // 将翻译文本添加到结果字符串中
                        translatedText.append(translation.at(0).toString());
                    }
                }

                // 返回提取的翻译文本
                return translatedText;
            }
        }
    }

    // 如果解析失败，返回空字符串
    return QString();
}
