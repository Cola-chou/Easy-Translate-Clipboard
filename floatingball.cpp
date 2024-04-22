#include "floatingball.h"
#include "ui_floatingball.h"
#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QScreen>

FloatingBall::FloatingBall(ContextMenuManager *contextMenuManager,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatingBall)
{
    ui->setupUi(this);
    // 获取屏幕大小
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    // 设置悬浮球初始位置为屏幕的右下角
    int windowWidth = width();
    int windowHeight = height();
    move(screenWidth-windowWidth*1,screenHeight-windowHeight*3);

    // 设置无边框和窗口层级
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // 设置窗口透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 鼠标追踪
    setMouseTracking(true);
    // 获取右键菜单
    __contextMenuManager = contextMenuManager;
    __floatingBallMenu = __contextMenuManager->getMenu();
}

FloatingBall::~FloatingBall()
{
    delete ui;
}

void FloatingBall::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿，不然会有明显锯齿
    painter.setRenderHint(QPainter::HighQualityAntialiasing); // 可选 用于更高质量的平滑边缘
    ImgRect = QRect(72,72,100,100);
//    painter.drawPixmap(ImgRect,QPixmap(":/images/floatingballImage/linux.png")); // 后期可替换为二次元
    painter.drawPixmap(ImgRect,QPixmap(":/images/floatingballImage/xdhs.png")); // 后期可替换为二次元
    QRect textBoxRect(ImgRect.left() - 120, ImgRect.top(), 200, 200);
    QWidget::paintEvent(event);
}

void FloatingBall::mousePressEvent(QMouseEvent* event)
{ // 鼠标按下事件
    if (event->buttons() & Qt::LeftButton)
    { // 鼠标左键按下
        qDebug() << "鼠标左键按下:" << (event->buttons() & Qt::LeftButton);
        // 记录 鼠标点击位置相对于窗口左上角的偏移量。
        m_dragStartPosition = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
    else if(event->buttons() & Qt::RightButton)
    { // 鼠标右键按下
         qDebug() << "鼠标右键按下:" << (event->buttons() & Qt::RightButton);

         // 显示右键菜单
         __floatingBallMenu->exec(event->globalPos());
    }
}

void FloatingBall::mouseDoubleClickEvent(QMouseEvent *event)
{ // 鼠标双击事件
    if(event->button() == Qt::LeftButton)
    {
        qDebug()<<"双击"<<event->pos();
        showWindowFlags = !showWindowFlags;
        qDebug()<<"showWindowFlags:"<<showWindowFlags;
        if(showWindowFlags)
            emit show_window();
        else
            emit hide_window();
    }
}

void FloatingBall::mouseMoveEvent(QMouseEvent* event)
{ // 鼠标移动事件
    if (event->buttons() == Qt::LeftButton) // 按位比较 ,检查鼠标左键是否按下
    {                                       // 此处使用buttons()函数
        // 移动窗口到当前鼠标位置
        QPoint newPoint = event->globalPos() - m_dragStartPosition;
        this->move(newPoint);
//        qDebug() << "窗口新位置:" << newPoint;
        event->accept();
    }
    //buttons()：
    //    buttons() 是 QMouseEvent 类中的函数，用于获取当前所有被按下的鼠标按钮。
    //    返回值是一个包含当前所有被按下的鼠标按钮的位掩码，可以通过与运算来检查某个特定按钮是否被按下。
    //button()：
    //    button() 也是 QMouseEvent 类中的函数，用于获取触发鼠标事件的按钮。
    //    返回值是一个 Qt::MouseButton 枚举值，表示触发事件的鼠标按钮。
}

void FloatingBall::mouseReleaseEvent(QMouseEvent *event)
{ // 鼠标释放事件
    event->accept();
}

void FloatingBall::listening(bool opt)
{ // 监听图标菜单 悬浮球右击action
    if(opt && isHidden())
        show();
    else
        if(!isHidden())
            setHidden(true);
}
