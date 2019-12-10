QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../apps.pri)

LIBS *= -lexe2 -lcore2 -lgui2

TARGET = VectorViewer

SOURCES += \
    DocumentIndex.cpp \
    MetaPerson.cpp \
    MetaVector.cpp \
    VVHomeCoverPage.cpp \
    VVHomeStack.cpp \
    VVIndexPage.cpp \
    Vector.cpp \
    VectorDocument.cpp \
    VectorGraph.cpp \
    VectorSetDocument.cpp \
    VectorSetGraphics.cpp \
    VectorSetGridPage.cpp \
    VectorSetStack.cpp \
    VectorSetSummaryPage.cpp \
    VectorSetWidget.cpp \
    main.cpp \
    VVMainWindow.cpp

HEADERS += \
    DocumentIndex.h \
    MetaPerson.h \
    MetaVector.h \
    VVHomeCoverPage.h \
    VVHomeStack.h \
    VVIndexPage.h \
    VVMainWindow.h \ \ \
    Vector.h \
    VectorDocument.h \
    VectorGraph.h \
    VectorSetDocument.h \
    VectorSetGraphics.h \
    VectorSetGridPage.h \
    VectorSetStack.h \
    VectorSetSummaryPage.h \
    VectorSetWidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../common/FT815/FT815375.xml \
    ../../common/PR598/PR598659.xml \
    ../../common/art/GradStack.svg \
    GradStack.jpg \
    VectorDocument
