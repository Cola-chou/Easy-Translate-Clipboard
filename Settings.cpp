#include "Settings.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QTableWidget>
#include "Singleton.hpp"

Settings::Settings(QWidget *parent) : QWidget(parent, Qt::Window)
{
    setWindowTitle("settings");
    setFixedSize(600, 400);
    settings = new QSettings("config.ini", QSettings::IniFormat);
    initSettings();
}

void Settings::showSettingWindow()
{
    this->show();
}


void Settings::initSettings()
{
    // 整体是一个垂直布局
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(10,10, 10, 10);
    main_layout->setSpacing(10);
    // 第一个布局, 即 设置标题
    QHBoxLayout* sub_layout_title = new QHBoxLayout(this);
    QLabel* settings_title = new QLabel(QObject::tr("设置"), this);
    sub_layout_title->addWidget(settings_title);
    // 滚动
    QHBoxLayout* sub_layout_body = new QHBoxLayout(this);
    QScrollArea* scroll_area = new QScrollArea(this);
    QVBoxLayout* scroll_layout = new QVBoxLayout(scroll_area);
    scroll_layout->setContentsMargins(10, 20, 10, 10);
    scroll_layout->setSpacing(10);
    // 第一个设置项目, 监听剪切板
    QHBoxLayout* sub_layout_clipboard = new QHBoxLayout(scroll_area);
    clipboard = new QCheckBox(scroll_area);
    bool state = settings->value("Clipboard", Qt::Unchecked).toBool();
    clipboard->setCheckState(state ? Qt::Checked : Qt::Unchecked);
    QLabel* clipboard_text = new QLabel(QObject::tr("监听剪切板"), scroll_area);
    sub_layout_clipboard->addSpacing(20);
    sub_layout_clipboard->addWidget(clipboard);
    sub_layout_clipboard->addSpacing(10);
    sub_layout_clipboard->addWidget(clipboard_text);
    sub_layout_clipboard->addStretch();
    //===

    // 语言设置
    //===
    scroll_layout->addLayout(sub_layout_clipboard);
    scroll_layout->addStretch();
    scroll_area->setLayout(scroll_layout);
    sub_layout_body->addWidget(scroll_area);
    
    // 确定，取消
    QHBoxLayout* sub_lay_last = new QHBoxLayout(this);
    QPushButton* confirm = new QPushButton(QObject::tr("确认"), this);
    QPushButton* cancel = new QPushButton(QObject::tr("取消"), this);
    sub_lay_last->addStretch();
    sub_lay_last->addWidget(confirm);
    sub_lay_last->addWidget(cancel);

    main_layout->addLayout(sub_layout_title);
    main_layout->addLayout(sub_layout_body);
    main_layout->addLayout(sub_lay_last);

    this->setLayout(main_layout);

    connect(confirm, &QPushButton::clicked, this, &Settings::confirm);
    connect(cancel, &QPushButton::clicked, this, &Settings::close);
}

void Settings::tabWidget()
{

    // 创建 QVBoxLayout 用于管理 mainWidget 的子控件  
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);

    // 创建 QTabWidget  
    QTabWidget* tabWidget = new QTabWidget;

    // 创建第一个页面  
    QWidget* tab1 = new QWidget;
    QLabel* label1 = new QLabel("这是第一个页面的内容");
    QVBoxLayout* layout1 = new QVBoxLayout(tab1);
    layout1->addWidget(label1);

    // 创建第二个页面  
    QWidget* tab2 = new QWidget;
    QLabel* label2 = new QLabel("这是第二个页面的内容");
    QVBoxLayout* layout2 = new QVBoxLayout(tab2);
    layout2->addWidget(label2);

    // 将页面添加到 QTabWidget 中  
    tabWidget->addTab(tab1, "页面1");
    tabWidget->addTab(tab2, "页面2");

    tabWidget->setStyleSheet("QTabWidget::pane { margin: 0px; padding: 0px;}");

    // 将 QTabWidget 添加到主容器的布局中  
    layout->addWidget(tabWidget);

    this->setLayout(layout);
}

void Settings::confirm()
{
    saveSettings();
    this->close();
    sendAll();
}

void Settings::saveSettings()
{
    settings->setValue("Clipboard", clipboard->checkState());
}

void Settings::sendAll()
{
    emit listen_clipboard(clipboard->checkState() == Qt::Checked);
}

