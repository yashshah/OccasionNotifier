#-------------------------------------------------
#
# Project created by QtCreator 2012-04-01T12:02:47
#
#-------------------------------------------------

QT       += core gui xml

TARGET = BirthdayNotifier
TEMPLATE = app


SOURCES += main.cpp\
    dataStorageInterface.cpp \
    dataStorageCSV.cpp \
    eventData.cpp \
    MainWindow.cpp \
    dataStorageXML.cpp

HEADERS  += \
    dataStorageInterface.h \
    dataStorageCSV.h \
    eventData.h \
    MainWindow.h \
    dataStorageXML.h

FORMS    += mainwindow.ui
