#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clipboardmonitor.h"
#include "ui_mainwindow.h"
#include "QUrlQuery"

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
    void updateClipboardContent(const QString &text);
    void translateText(const QString &text);
    QString extractTranslatedText(const QByteArray &responseData);
    void IniComboBox();

    void on_cmbInput_currentIndexChanged(int index);

    void on_cmbOutput_currentIndexChanged(int index);

    void on_btnChange_clicked();

    void onListenClipboardToggled(bool checked);

private:
    Ui::MainWindow *ui;
    Language l_EN,l_ZH;
    ClipboardMonitor *clipboardMonitor;
    QNetworkAccessManager *networkManager;
    QUrl  createQueryUrl(QString text);
    void toTray();
};
#endif // MAINWINDOW_H
