#pragma once

#include <QObject>

#include <QByteArray>
#include <QDomElement>
#include <QList>
#include <QMap>
#include <QFileInfo>

#include "UnitFloat.h"
#include "UnitFloatVector.h"
#include "Vector.h"
#include "VectorData.h"

class VectorObject : public QObject
{
    Q_OBJECT
public:
    typedef QList<VectorObject * > List;
    typedef QMap<Vector::FileScope, VectorObject *> Map;
    typedef QMap<QString, VectorObject *> NameMap;

public:
    explicit VectorObject(const Vector::FileScope scope,
                           QObject * parent=nullptr);
    Vector::FileScope scope(void) const { return cmScope; }
    VectorData data(void) const { return mData; }
    VectorData & data(void) { return mData; }
    int vectorSize(void) const { return mCoefVector.size(); }
    UnitFloatVector coefVector(void) const
    { return mCoefVector; }
    UnitFloat::Value at(const int x);

signals:
    void openCancelled(Vector::FileScope scope);
    void opened(VectorObject * vector);
    void vectorClosed(Vector::FileScope scope);

public slots:
    void openFileName(const QString & fileName);
    void close(void);

private slots:
    void readPngFile(void);
    void readXmlFile(void);
    void getRootElement(void);
    void parseVectorElement(void);
    void setVectorCoefData(void);

private:
    const Vector::FileScope cmScope=Vector::nullScope;
    QFileInfo mFileInfo;
    VectorData mData;
    UnitFloatVector mCoefVector;
};

