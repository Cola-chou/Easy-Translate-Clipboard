#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "QJsonArray"
#include "QUrlQuery"
#include "QSystemTrayIcon"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置图标
    setWindowIcon(QIcon(":/images/icons/aa.ico"));

    toTray();

    this->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);

    ui->textOutPut->setReadOnly(true); // plaintextedit只读

    IniComboBox();
    clipboardMonitor = new ClipboardMonitor(this);
    connect(clipboardMonitor, &ClipboardMonitor::clipboardChanged, this, &MainWindow::translateText);
    networkManager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClipboardContent(const QString &text)
{
    ui->textInput->setText(text);
}

void MainWindow::translateText(const QString &text)
{ // 翻译
    // 更新输入框
    updateClipboardContent(text);

    qDebug() << "正在翻译文本：" << text;

    // 拼接url
    QUrl url = createQueryUrl(text);

    // 网络通信
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();

            // 进行翻译结果处理
            QString translatedText = extractTranslatedText(data);
             qDebug() << "翻译成功";

            ui->textOutPut->clear();
            QFont font  = ui->textOutPut->font();
            font.setWeight(32);
            ui->textOutPut->setFont(font);
            ui->textOutPut->appendPlainText(translatedText);

            // 显示窗口
            this->showNormal();
            this->activateWindow(); // 激活窗口，确保它处于前台
        } else {
            qDebug() << "网络错误：" << reply->errorString();
            ui->textOutPut->appendPlainText(reply->errorString());
        }
        reply->deleteLater();
    });
}

QString MainWindow::extractTranslatedText(const QByteArray &responseData)
{
    // 解析 JSON 响应
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

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
                for (const QJsonValue &value : translations) {
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

void MainWindow::IniComboBox()
{
    l_EN.text = "英语";
    l_EN.code = LanguageCode::EN;
    l_ZH.text = "汉语";
    l_ZH.code = LanguageCode::ZH;

    ui->cmbInput->addItem(l_EN.text,l_EN.code);
    ui->cmbInput->addItem(l_ZH.text,l_ZH.code);
    ui->cmbOutput->addItem(l_EN.text,l_EN.code);
    ui->cmbOutput->addItem(l_ZH.text,l_ZH.code);

    ui->cmbInput->setCurrentIndex(l_EN.code);
    ui->cmbOutput->setCurrentIndex(l_ZH.code);
}

void MainWindow::on_cmbInput_currentIndexChanged(int index)
{
    qDebug()<<"cmbInput："<<index;
//    ui->cmbOutput->setCurrentIndex(l_EN.code);
}

void MainWindow::on_cmbOutput_currentIndexChanged(int index)
{
    qDebug()<<"cmbOutput："<<index;
//    ui->cmbInput->setCurrentIndex(l_EN.code);
}

void MainWindow::on_btnChange_clicked()
{
    int tmpIndex = ui->cmbOutput->currentIndex();
    ui->cmbOutput->setCurrentIndex(ui->cmbInput->currentIndex());
    ui->cmbInput->setCurrentIndex(tmpIndex);
}

QUrl MainWindow::createQueryUrl(QString text)
{
    // Define base URL
    QString baseUrl = "https://translate.googleapis.com/translate_a/single";

    // Create URL query parameters
    QUrlQuery query;
    query.addQueryItem("client", "gtx");
    query.addQueryItem("sl", "auto");

    if(ui->cmbOutput->currentIndex() == LanguageCode::EN)
        query.addQueryItem("tl","en");
    else
        query.addQueryItem("tl","zh-CN");
    query.addQueryItem("dt","t");
    query.addQueryItem("q",text);

    QUrl url(baseUrl);
    url.setQuery(query);
    qDebug()<<"url: "<<url.toString();

    return  url;
}

void MainWindow::toTray()
{ // 创建托盘
    // 新建QSystemTrayIcon对象
    QSystemTrayIcon *tray = new QSystemTrayIcon(this);
    // 新建托盘要显示的icon
    QIcon icon = QIcon(":/images/icons/aa.ico");
    // 设置托盘icon
    tray->setIcon(icon);
    // 设置托盘鼠标悬浮显示内容
    tray->setToolTip("翻译");
    // 创建菜单事件
    QAction *actShowWindow  = new QAction("打开主界面",this);
    connect(actShowWindow,&QAction::triggered,[this]{this->show();});
    QAction *actListenClipboard = new QAction("监听剪贴板",this);
    actListenClipboard->setCheckable(true);
    actListenClipboard->setChecked(true);
    connect(actListenClipboard,SIGNAL(toggled(bool)),this,SLOT(onListenClipboardToggled(bool)));
    QAction *actExit = new QAction("退出",this);
    connect(actExit,&QAction::triggered,[this]{this->close();});
    // 创建菜单
    QMenu *menu = new QMenu(this);
    // 新增一个菜单
    menu->addAction(actShowWindow);
    menu->addAction(actListenClipboard);
    // 增加分割符
    menu->addSeparator();
    // 新增一个菜单
    menu->addAction(actExit);
    // 给托盘加入菜单
    tray->setContextMenu(menu);
    // 给托盘绑定事件
    connect(tray,&QSystemTrayIcon::activated,[this](QSystemTrayIcon::ActivationReason action){
        switch (action) {
        case QSystemTrayIcon::Unknown:
            qDebug()<<"未知事件";
            break;
        case QSystemTrayIcon::Context:
            qDebug()<<"右键点击了图标(请求托盘上下文)";
            break;
        case QSystemTrayIcon::Trigger:
            qDebug()<<"单机了图标";
            break;
        case QSystemTrayIcon::DoubleClick:
            qDebug()<<"双击了图标(双击也会触发单击中)";
            break;
        case QSystemTrayIcon::MiddleClick:
            qDebug()<<"鼠标中间点击了图标";
            break;
        }
    });
    tray->show();
}

void MainWindow::onListenClipboardToggled(bool checked)
{ // 监听剪贴板槽函数
    if(checked)
        clipboardMonitor->startListening();
    else
        clipboardMonitor->stopListening();
}
