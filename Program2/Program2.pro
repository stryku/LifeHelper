#-------------------------------------------------
#
# Project created by QtCreator 2016-07-10T00:48:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Program1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sources/src/internals/controller/P2Controller.cpp \
    sources/src/internals/controller/P2QtController.cpp \
    sources/src/internals/input/P2Input.cpp \
    sources/src/internals/input/P2InputHandler.cpp \
    sources/src/internals/input/P2InputObserver.cpp \
    sources/src/internals/input/P2InputProvider.cpp \
    sources/src/internals/model/P2Model.cpp \
    sources/src/internals/model/P2ModelObserver.cpp \
    sources/src/internals/view/detail/P2QtWidgetManager.cpp \
    sources/src/internals/view/P2ConsoleView.cpp \
    sources/src/internals/view/P2QtView.cpp \
    sources/src/internals/view/P2View.cpp \
    sources/src/main.cpp \
    sources/src/mainwindow.cpp \
    sources/src/ProgramFactory.cpp \
    sources/src/ViewFactory.cpp

HEADERS  += \
    sources/inc/mainwindow.h \
    sources/inc/ProgramFactory.h \
    sources/inc/ViewFactory.h \
    sources/inc/internals/controller/P2Controller.h \
    sources/inc/internals/controller/P2QtController.h \
    sources/inc/internals/input/P2Input.h \
    sources/inc/internals/input/P2InputHandler.h \
    sources/inc/internals/input/P2InputObserver.h \
    sources/inc/internals/input/P2InputProvider.h \
    sources/inc/internals/model/P2Model.h \
    sources/inc/internals/model/P2ModelObserver.h \
    sources/inc/internals/view/detail/P2QtWidgetManager.h \
    sources/inc/internals/view/P2ConsoleView.h \
    sources/inc/internals/view/P2QtView.h \
    sources/inc/internals/view/P2View.h \
    sources/inc/internals/ProgramInternals.h

DISTFILES += \
    CMakeLists.txt

FORMS += \
    uiforms/mainwindow.ui
