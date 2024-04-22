#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "Translation.h"
#include "trayicon.h"
#include "Settings.h"
#include "floatingball.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QNetworkAccessManager;

enum LanguageCode {EN,ZH };
struct Language
{
    QString text;
    LanguageCode code;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
//    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent* event) override;
private slots:
    // 响应交换按钮的槽函数
    void on_btnChange_clicked();
    // 响应剪切板内容更新的槽函数
    void updateClipboardContent(const QString&);
    // 
    void translationFinished(const QString&);
    void existText();

signals:
    void text_changed(const QString& text);
    void swap_btn_clicked(const QString& text);

private:
    Ui::MainWindow *ui;
    Translation* __translation;
    TrayIcon* __trayicon;
    Settings* __settings;
    FloatingBall* __floatingBall;
};
#endif // MAINWINDOW_H
