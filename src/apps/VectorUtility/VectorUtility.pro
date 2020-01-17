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
    AbstractCentralPage.cpp \
    BaseColorSet.cpp \
    CentralStack.cpp \
    GraphPage.cpp \
    GridPage.cpp \
    HomePage.cpp \
    MainWindow-Setup.cpp \
    QObjectInfo.cpp \
    RawXmlPage.cpp \
    ReconPage.cpp \
    SummaryPage.cpp \
    SummaryView.cpp \
    UnitFloat.cpp \
    UnitFloatLabel.cpp \
    UnitFloatVector.cpp \
    UnitVectorGraph.cpp \
    VariantMatrix.cpp \
    Vector.cpp \
    VectorColumn.cpp \
    VectorColumnSet.cpp \
    VectorColumnTableWidget.cpp \
    VectorColumnTwig.cpp \
    VectorData.cpp \
    VectorObject.cpp \
    VectorUtilityApp.cpp \
    main.cpp \
    MainWindow.cpp \

HEADERS += \
    AbstractCentralPage.h \
    BaseColorSet.h \
    CentralStack.h \
    DataProperty.h \
    Debug.h \
    DualMap.h \
    GraphPage.h \
    GridPage.h \
    HomePage.h \
    MainWindow.h \
    Matrix.h \
    QObjectInfo.h \
    QProperty.h \
    QQVector.h \
    RawXmlPage.h \
    ReconPage.h \
    SummaryPage.h \
    SummaryView.h \
    UnitFloat.h \
    UnitFloatLabel.h \
    UnitFloatVector.h \
    UnitVectorGraph.h \
    VariantMatrix.h \
    Vector.h \
    VectorColumn.h \
    VectorColumnSet.h \
    VectorColumnTableWidget.h \
    VectorColumnTwig.h \
    VectorData.h \
    VectorObject.h \ \
    VectorUtilityApp.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \ \
    BlankPage-cpp.txt \
    BlankPage-h.txt \
    Notes.txt \
    TraceD20200116T1632.txt

RESOURCES += \
    VectorUtility.qrc
