TEMPLATE = app

QT += qml quick widgets network

SOURCES += main.cpp \
    dltwinballmanager.cpp \
    networkmanager.cpp \
    localdatamanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    UC.txt \
    note.txt

HEADERS += \
    constant.h \
    dltwinballmanager.h \
    networkmanager.h \
    localdatamanager.h


