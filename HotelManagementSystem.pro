#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T14:53:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotelManagementSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += sql

SOURCES += \
        main.cpp \
    staff.cpp \
    login.cpp \
    manage.cpp \
    register.cpp \
    takeinwidget.cpp \
    checkroom.cpp \
    checkaccount.cpp \
    book.cpp \
    arrival.cpp \
    addroom.cpp \
    roomstate.cpp \
    takeoutwidget.cpp

HEADERS += \
    staff.h \
    login.h \
    manage.h \
    register.h \
    takeinwidget.h \
    checkroom.h \
    checkaccount.h \
    book.h \
    arrival.h \
    addroom.h \
    roomstate.h \
    takeoutwidget.h

FORMS += \
    staff.ui \
    login.ui \
    manage.ui \
    register.ui \
    takeinwidget.ui \
    checkroom.ui \
    checkaccount.ui \
    book.ui \
    arrival.ui \
    addroom.ui \
    roomstate.ui \
    takeoutwidget.ui
