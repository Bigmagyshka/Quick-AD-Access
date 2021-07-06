QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += relise


VERSION = 0.6

QMAKE_TARGET_COMPANY = BiGMaG
QMAKE_TARGET_PRODUCT = Quick_AD_Access
QMAKE_TARGET_COPYRIGHT = BiGMaG
RC_ICONS =  Sourse/m.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Containers/card.cpp \
    Containers/client.cpp \
    Containers/sity.cpp \
    My_error.cpp \
    ask.cpp \
    delete_db.cpp \
    edit_db.cpp \
    main.cpp \
    mainwindow.cpp \
    start_window.cpp

HEADERS += \
    Containers/card.h \
    Containers/client.h \
    Containers/sity.h \
    My_error.h \
    ask.h \
    delete_db.h \
    edit_db.h \
    mainwindow.h \
    start_window.h

FORMS += \
    Containers/card.ui \
    Containers/client.ui \
    Containers/sity.ui \
    My_error.ui \
    ask.ui \
    delete_db.ui \
    edit_db.ui \
    mainwindow.ui \
    start_window.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
        Sourse/logo.png \
	Sourse/main_db.db
