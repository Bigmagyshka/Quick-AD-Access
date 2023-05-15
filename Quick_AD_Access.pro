QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++11


VERSION = 0.78
DEFINES += APP_VERSION=$$VERSION

QMAKE_TARGET_COMPANY = BiGMaG
QMAKE_TARGET_PRODUCT = Quick_AD_Access
QMAKE_TARGET_COPYRIGHT = BiGMaG
RC_ICONS =  Sourse/m.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Containers/ADButton.cpp \
    Containers/AdditionalInfoDlg.cpp \
    Containers/Card.cpp \
    Containers/CardData.cpp \
    EditDB/addworker.cpp \
    EditDB/moveconnection.cpp \
    My_error.cpp \
    TrialDlg/trialversiondlg.cpp \
    ask.cpp \
    delete_db.cpp \
    edit_db.cpp \
    main.cpp \
    mainwindow.cpp \
    start_window.cpp

HEADERS += \
    Containers/ADButton.h \
    Containers/AdditionalInfoDlg.h \
    Containers/Card.h \
    Containers/CardData.h \
    EditDB/addworker.h \
    EditDB/moveconnection.h \
    My_error.h \
    TrialDlg/trialversiondlg.h \
    ask.h \
    delete_db.h \
    edit_db.h \
    mainwindow.h \
    start_window.h

FORMS += \
    Containers/AdditionalInfoDlg.ui \
    Containers/Card.ui \
    EditDB/addworker.ui \
    EditDB/moveconnection.ui \
    My_error.ui \
    TrialDlg/trialversiondlg.ui \
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
    Sourse/m.ico \
	Sourse/main_db.db
