QT       += core gui
QT += network
Qt += ssl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Network.cpp \
    Settings.cpp \
    #Singleton.cpp \
    Translation.cpp \
    TrayIcon.cpp \
    clipboardmonitor.cpp \
    contextmenumanager.cpp \
    floatingball.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Network.h \
    Settings.h \
    #Singleton.hpp \
    Translation.h \
    clipboardmonitor.h \
    contextmenumanager.h \
    floatingball.h \
    mainwindow.h \
    trayicon.h \
    ui_mainwindow.h

FORMS += \
    floatingball.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc


#程序版本
VERSION = 1.0.0.0
#程序图标
RC_ICONS = icons/aa.ico
#公司名称
QMAKE_TARGET_COMPANY ="春秋鼎盛"
#程序说明
QMAKE_TARGET_DESCRIPTION = "监听剪贴板，有新内容自动弹出翻译，使用谷歌翻译api"
#版权信息
QMAKE_TARGET_COPYRIGHT = "Copyright(C) 2024"
#程序名称
QMAKE_TARGET_PRODUCT = "随译"
#程序语言
#0x0800代表和系统当前语言一致
RC_LANG = 0x0800

DISTFILES += \
    README.md
