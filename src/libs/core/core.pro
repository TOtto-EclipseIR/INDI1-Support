QT *= xml
#QT -= gui

TEMPLATE = lib
DEFINES += CORE_LIBRARY

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

include(../libs.pri)

LIBS *= -lbase2

SOURCES += \
    BasicId.cpp \
    BasicName.cpp \
    Core.cpp \
    Variable.cpp \
    VariableId.cpp \
    VariableIdList.cpp \
    VariableMap.cpp \
    VariableSet.cpp \
    VariableSetDocument.cpp \
    VariableSetDocumentObject.cpp \
    VariableType.cpp

HEADERS += \
    BasicId.h \
    BasicName.h \
    Variable.h \
    VariableId.h \
    VariableIdList.h \
    VariableMap.h \
    VariableSet.h \
    VariableSetDocument.h \
    VariableSetDocumentObject.h \
    VariableType.h \
    core_global.h \
    Core.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../libs.pri
