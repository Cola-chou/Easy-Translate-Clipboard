#ifndef FLOATINGBALL_H
#define FLOATINGBALL_H
#include "contextmenumanager.h"
#include <QWidget>

namespace Ui {
class FloatingBall;
}

class FloatingBall : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit FloatingBall(ContextMenuManager *contextMenuManager,QWidget *parent = nullptr);
    ~FloatingBall();
    void listening(bool opt);

private:
    Ui::FloatingBall *ui;
    ContextMenuManager *__contextMenuManager;                   // 右键菜单管理器
    QMenu *__floatingBallMenu;                                  // 右键菜单
    QPoint m_dragStartPosition;                                 //
    QRect ImgRect;                                              // 图片尺寸
    int  ImgRedius = 0;                                         // 图片圆半径
    bool m_mouseEventsEnabled = true;                           // mousepressEvent禁用开启标志
    bool showWindowFlags = false;                                   // 是否显示文本框
signals:
    void show_window();                              // 显示主窗口信号
    void hide_window();                              // 隐藏主窗口信号
};

#endif // FLOATINGBALL_H
