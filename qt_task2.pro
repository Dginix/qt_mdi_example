QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datathread.cpp \
    indicatorwidget.cpp \
    main.cpp \
    mainmdichild.cpp \
    mainwindow.cpp \
    processmdichild.cpp \
    qcustomplot.cpp \
    mdichild.cpp \
    extendedslider.cpp

HEADERS += \
    datathread.h \
    indicatorwidget.h \
    mainmdichild.h \
    mainwindow.h \
    mdichildtype.h \
    processmdichild.h \
    qcustomplot.h \
    mdichild.h \
    extendedslider.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
