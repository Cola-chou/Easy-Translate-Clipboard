#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "Translation.h"
#include "TrayIcon.h"

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

private slots:
    void on_btnChange_clicked();

    void updateClipboardContent(const QString&);
    void translation_finished(const QString&);
    void exist_text();

signals:
    void textChanged(const QString& text);
    void swapBtnClicked(const QString& text);

private:
    Ui::MainWindow *ui;
    Translation* __translation;
    TrayIcon* __trayicon;
};
#endif // MAINWINDOW_H
