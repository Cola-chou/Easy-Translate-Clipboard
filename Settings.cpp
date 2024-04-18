#include "Settings.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QMainWindow>
#include "Singleton.hpp"

Settings::Settings(QWidget *parent) : QWidget(parent, Qt::Window)
{
    setWindowTitle("settings");
    setFixedSize(600, 400);
    initSettings();
}

void Settings::showSettingWindow()
{
    this->show();
}

void Settings::initSettings()
{
    QVBoxLayout * layout = new QVBoxLayout(this);
    //  边距
    layout->setContentsMargins(0,20, 0, 0);
    // 控件距离
    layout->setSpacing(10);

    QHBoxLayout* sub_layout1 = new QHBoxLayout(this);
    sub_layout1->addStretch(); // 添加伸缩空间，让CheckBox和Label居中对齐
    QCheckBox* checkBox = new QCheckBox(this);
    sub_layout1->addWidget(checkBox);
    sub_layout1->addStretch();
    QLabel* label = new QLabel(this);
    label->setText(u8"配置项1");
    label->setFixedWidth(200);
    sub_layout1->addWidget(label);

    layout->addLayout(sub_layout1);
    layout->addStretch();

    setLayout(layout);
}

