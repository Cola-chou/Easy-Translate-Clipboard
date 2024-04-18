#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "QJsonArray"
#include "QUrlQuery"
#include "QSystemTrayIcon"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置图标
    setWindowIcon(QIcon(":/images/icons/aa.ico"));

    this->setWindowFlags(Qt::Window);

    ui->textOutPut->setReadOnly(true); // plaintextedit只读

    __trayicon = new TrayIcon(this);
    __translation = new Translation(this);

    __translation->initComboBox(ui->cmbInput, Translation::EN_US);
    __translation->initComboBox(ui->cmbOutput, Translation::ZH_CN);

    connect(__trayicon, &TrayIcon::show_window, this, &MainWindow::show);
    connect(__trayicon, &TrayIcon::close_window, QApplication::instance(), &QApplication::quit);
    //connect(__trayicon, &TrayIcon::close_window, this, &MainWindow::close);
    connect(__trayicon, &TrayIcon::hide_window, this, &MainWindow::hide);
    connect(__trayicon, &TrayIcon::listen_clipboard_toggled, __translation, &Translation::listen_clipboard_toggled);
    connect(__translation, &Translation::translation_finished, this, &MainWindow::translation_finished);
    connect(__translation, &Translation::translation_error, this, &MainWindow::translation_error);
    connect(__translation, &Translation::clipboard_data, this, &MainWindow::updateClipboardContent);
    connect(this, &MainWindow::textChanged, __translation, &Translation::translation);
    connect(ui->textInput, &QTextEdit::textChanged, this, &MainWindow::exist_text);

    __trayicon->showTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete __trayicon;
    delete __translation;
}

void MainWindow::updateClipboardContent(const QString& text)
{
    ui->textInput->setText(text);
}

void MainWindow::on_btnChange_clicked()
{
    int tmpIndex = ui->cmbOutput->currentIndex();
    ui->cmbOutput->setCurrentIndex(ui->cmbInput->currentIndex());
    ui->cmbInput->setCurrentIndex(tmpIndex);
}

void MainWindow::translation_finished(const QString& text) {
    ui->textOutPut->setPlainText(text);
}

void MainWindow::translation_error(const QString& text) {
    ui->textOutPut->setPlainText(text);
}

void  MainWindow::exist_text() {
    QString text = ui->textInput->toPlainText();
    emit textChanged(text);
}


