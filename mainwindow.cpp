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

     __contextMenuManager = new ContextMenuManager();
    __trayicon = new TrayIcon(__contextMenuManager,this);
    __translation = new Translation(this);
    __settings = new Settings(this);
    __floatingBall = new FloatingBall(__contextMenuManager);
    __translation->initComboBox(ui->cmbInput, Translation::EN_US);
    __translation->initComboBox(ui->cmbOutput, Translation::ZH_CN);

    connect(__trayicon, &TrayIcon::show_window, this, &MainWindow::show);
    connect(__trayicon, &TrayIcon::close_window, QApplication::instance(), &QApplication::quit);
    //connect(__trayicon, &TrayIcon::close_window, this, &MainWindow::close);
    connect(__trayicon, &TrayIcon::hide_window, this, &MainWindow::hide);

    connect(__floatingBall, &FloatingBall::show_window, this, &MainWindow::show);
    connect(__floatingBall, &FloatingBall::hide_window, this, &MainWindow::hide);

    connect(__trayicon, &TrayIcon::listen_clipboard_toggled, __translation, &Translation::listenClipboardToggled);
    connect(__trayicon, &TrayIcon::open_setting, __settings, &Settings::show);
    connect(__settings, &Settings::listen_clipboard, __translation, &Translation::listenClipboardToggled);
    connect(__trayicon,&TrayIcon::open_floatingBall_toggled,__floatingBall,&FloatingBall::listening);
    connect(__translation, &Translation::translation_finished, this, &MainWindow::translationFinished);
    connect(__translation, &Translation::clipboard_data, this, &MainWindow::updateClipboardContent);
    connect(this, &MainWindow::text_changed, __translation, &Translation::translation);
    connect(this, &MainWindow::swap_btn_clicked, __translation, &Translation::swapLanage);
    
    connect(ui->textInput, &QTextEdit::textChanged, this, &MainWindow::existText);

    __trayicon->showTrayIcon();
    __floatingBall->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete __settings;
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
    emit swap_btn_clicked(text);
}

void MainWindow::translationFinished(const QString& text) {
    ui->textOutPut->setPlainText(text);
}

void MainWindow::existText() {
    QString text = ui->textInput->toPlainText();
    emit text_changed(text);
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


