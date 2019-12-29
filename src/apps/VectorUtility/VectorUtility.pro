QT       += core gui xml svg

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

SOURCES += \
    MainWindow-Setup.cpp \
    UnitFloat.cpp \
    UnitFloatLabel.cpp \
    UnitFloatVector.cpp \
    Vector.cpp \
    VectorData.cpp \
    VectorItemDelegate.cpp \
    VectorItemModel.cpp \
    VectorObject.cpp \
    VectorTableHorizontalHeader.cpp \
    VectorTableIndex.cpp \
    VectorTableItem.cpp \
    VectorTableModel.cpp \
    VectorTableVerticalHeader.cpp \
    VectorTableView.cpp \
    VectorTableWidget.cpp \
    VectorUtilityApp.cpp \
    main.cpp \
    MainWindow.cpp \

HEADERS += \
    DataProperty.h \
    Debug.h \
    MainWindow.h \
    Matrix.h \
    QProperty.h \
    UnitFloat.h \
    UnitFloatLabel.h \
    UnitFloatVector.h \
    Vector.h \
    VectorData.h \
    VectorItemDelegate.h \
    VectorItemModel.h \
    VectorObject.h \ \
    VectorTableHorizontalHeader.h \
    VectorTableIndex.h \
    VectorTableItem.h \
    VectorTableModel.h \
    VectorTableVerticalHeader.h \
    VectorTableView.h \
    VectorTableWidget.h \
    VectorUtilityApp.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
