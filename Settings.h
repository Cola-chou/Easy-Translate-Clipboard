#pragma once

#include <QWidget>
#include <QSettings>

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget*parent = nullptr);

public slots:
    void showSettingWindow();
private:
    void initSettings();

};
