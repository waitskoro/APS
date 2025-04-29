QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection/connectionmanager.cpp \
    connection/socket/tcpsocket.cpp \
    connection/xmlparser.cpp \
    main.cpp \
    view/authform.cpp \
    view/connection/connectionlist.cpp \
    view/connection/delegate.cpp \
    view/loader.cpp \
    view/mainwindow.cpp

HEADERS += \
    connection/connectioninfo.h \
    connection/connectionmanager.h \
    connection/connectionstatus.h \
    connection/iconnectionparameters.h \
    connection/socket/itcpsocket.h \
    connection/socket/socketinfo.h \
    connection/socket/tcpsocket.h \
    connection/xmlparser.h \
    view/authform.h \
    view/connection/connectionlist.h \
    view/connection/delegate.h \
    view/loader.h \
    view/mainwindow.h

FORMS += \
    view/authform.ui \
    view/loader.ui \
    view/mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    view/source/loader.gif
