QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankTimer.cpp \
    chooseaccount.cpp \
    finished.cpp \
    main.cpp \
    mainwindow.cpp \
    saldo.cpp \
    selection.cpp \
    settings.cpp \
    signin.cpp \
    transactions.cpp \
    uitemplate.cpp\
    RESTClient.cpp \
    withdrowal.cpp

HEADERS += \
    AccountTypes.h \
    Actions.h \
    bankTimer.h \
    chooseaccount.h \
    finished.h \
    mainwindow.h \
    saldo.h \
    selection.h \
    settings.h \
    signin.h \
    states.h \
    transactions.h \
    uitemplate.h\
    RESTClient.h \
    withdrowal.h

FORMS += \
    chooseaccount.ui \
    finished.ui \
    mainwindow.ui \
    saldo.ui \
    selection.ui \
    signin.ui \
    transactions.ui \
    uitemplate.ui \
    withdrowal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .atm_settings.ini
