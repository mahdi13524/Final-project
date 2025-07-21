QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcustomerwindow.cpp \
    adminmanagerwindow.cpp \
    adminwindow.cpp \
    bank_system.cpp \
    changepinwindow.cpp \
    createaccountwindow.cpp \
    customerwindow.cpp \
    deleteaccountwindow.cpp \
    edituserwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    showaccountswindow.cpp \
    transferwindow.cpp
    addcustomerwindow.cpp


HEADERS += \
    addcustomerwindow.h \
    adminmanagerwindow.h \
    adminwindow.h \
    bank_system.h \
    changepinwindow.h \
    createaccountwindow.h \
    customerwindow.h \
    deleteaccountwindow.h \
    edituserwindow.h \
    loginwindow.h \
    mainwindow.h \
    showaccountswindow.h \
    transferwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    untitled_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
