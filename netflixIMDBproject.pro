QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcommentdialog.cpp \
    addrowdialog.cpp \
    detailwindow.cpp \
    filterdialog.cpp \
    helpwindow.cpp \
    logowidget.cpp \
    main.cpp \
    mainwindow.cpp \
    sortdialog.cpp \
    viewcommentsdialog.cpp

HEADERS += \
    addcommentdialog.h \
    addrowdialog.h \
    comment.h \
    customsortfilterproxymodel.h \
    detailwindow.h \
    filterdialog.h \
    helpwindow.h \
    logowidget.h \
    mainwindow.h \
    sortdialog.h \
    viewcommentsdialog.h

FORMS += \
    addcommentdialog.ui \
    addrowdialog.ui \
    detailwindow.ui \
    filterdialog.ui \
    helpwindow.ui \
    mainwindow.ui \
    sortdialog.ui \
    viewcommentsdialog.ui

TRANSLATIONS += \
    netflixIMDBproject_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
