QT       += core gui
QT       += multimedia multimediawidgets
QT       += sql
RC_ICONS = Head.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mp3dec.cpp \
    mp3linklist.cpp \
    musicSql.cpp


HEADERS += \
    mainwindow.h \
    mp3IncludeHeader.h \
    mp3dec.h \
    mp3linklist.h \
    musicSql.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    docs.qrc \
    res_Icon.qrc

DISTFILES +=
