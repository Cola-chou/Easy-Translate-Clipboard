#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QJsonObject>

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
    connect(__translation, &Translation::clipboard_data, this, &MainWindow::updateClipboardContent);
    connect(this, &MainWindow::textChanged, __translation, &Translation::translation);
    connect(this, &MainWindow::swapBtnClicked, __translation, &Translation::swapLanage);
    
    connect(ui->textInput, &QTextEdit::textChanged, this, &MainWindow::exist_text);

    __trayicon->showTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClipboardContent(const QString& text)
{
    ui->textInput->setText(text);
    emit __trayicon->show_window();
}

void MainWindow::on_btnChange_clicked()
{
    int tmpIndex = ui->cmbOutput->currentIndex();
    ui->cmbOutput->setCurrentIndex(ui->cmbInput->currentIndex());
    ui->cmbInput->setCurrentIndex(tmpIndex);
    QString text = ui->textInput->toPlainText();
    emit swapBtnClicked(text);
}

void MainWindow::translation_finished(const QString& text) {
    ui->textOutPut->setPlainText(text);
}

void MainWindow::exist_text() {
    QString text = ui->textInput->toPlainText();
    emit textChanged(text);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (this->isVisible()) {
        // 如果窗口可见，隐藏主窗口并阻止事件进一步传播  
        this->hide();
        event->ignore();
        __trayicon->setflags(false);
    }
    else {
        // 否则，允许窗口关闭  
        event->accept();
    }
}


