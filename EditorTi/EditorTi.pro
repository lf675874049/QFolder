#-------------------------------------------------
#
# Project created by QtCreator 2015-01-13T16:50:36
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditorTi
TEMPLATE = app


SOURCES += main.cpp\
        editorwindow.cpp \
    subwindow.cpp \
    subdialog.cpp \
    splashdialog.cpp \
    editor/uniteditor.cpp \
    helper/editordb.cpp \
    model/unitmodel.cpp \
    model/unitmodel_extend.cpp

HEADERS  += editorwindow.h \
    subwindow.h \
    subdialog.h \
    splashdialog.h \
    editor/uniteditor.h \
    helper/editordb.h \
    model/unitmodel.h

FORMS    += editorwindow.ui \
    subwindow.ui \
    splashdialog.ui \
    editor/uniteditor.ui
