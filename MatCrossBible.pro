CONFIG += qt \
    release \
    warn_on
QT += core \
    gui \
    widgets \
    network \
    multimedia \
    multimediawidgets
qtHaveModule(printsupport): QT += printsupport
HEADERS += src/datatypes.h \
    src/trstrings.h \
    src/mainobject.h \
    src/icons.h \
    src/mdock.h \
    src/tmenu.h \
    src/highlighter.h \
    src/textview.h \
    src/fastaccesswidget.h \
    src/bookswidget.h \
    src/bookmarkswidget.h \
    src/mainwindow.h \
    src/settingsdialog.h \
    src/extextwindow.h \
    src/eximagewindow.h \
    src/searchtoolbar.h \
    src/wwwresources.h \
    src/utility.h \
    src/dictionary.h \
    src/httpaccess.h \
    src/audiotoolbar.h \
    src/projectortoolbar.h
SOURCES += src/main.cpp \
    src/trstrings.cpp \
    src/trstrings_embed.cpp \
    src/mainobject.cpp \
    src/icons.cpp \
    src/mdock.cpp \
    src/tmenu.cpp \
    src/highlighter.cpp \
    src/textview.cpp \
    src/fastaccesswidget.cpp \
    src/bookswidget.cpp \
    src/bookmarkswidget.cpp \
    src/mainwindow.cpp \
    src/settingsdialog.cpp \
    src/extextwindow.cpp \
    src/eximagewindow.cpp \
    src/searchtoolbar.cpp \
    src/wwwresources.cpp \
    src/utility.cpp \
    src/dictionary.cpp \
    src/httpaccess.cpp \
    src/audiotoolbar.cpp \
    src/projectortoolbar.cpp
FORMS += src/authenticationdialog.ui
RESOURCES += resources/resources.qrc
RC_FILE = resources/resources.rc
DESTDIR = bin
MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build
TEMPLATE = app
TARGET = MatCrossBible
