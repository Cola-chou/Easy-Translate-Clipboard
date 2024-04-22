#pragma once

#include <QCheckBox>
#include <QWidget>
#include <QSettings>
#include <tuple>

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget*parent = nullptr);
    void saveSettings();

    signals:
        void listen_clipboard(bool);

public slots:
    void showSettingWindow();
    void confirm();

private:
    void initSettings();
    void tabWidget();
    void sendAll();

private:
    QCheckBox* clipboard;
    QSettings* settings;
};
