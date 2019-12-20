#pragma once

#include <QObject>

#include <QByteArray>
#include <QDomElement>
#include <QList>
#include <QMap>
#include <QFileInfo>

#include "Vector.h"
#include "VectorData.h"

class VectorObject : public QObject
{
    Q_OBJECT
public:
    typedef QList<VectorObject * > List;
    typedef QMap<Vector::FileScope, VectorObject * > Map;

public:
    explicit VectorObject(const Vector::FileScope scope,
                           QObject * parent=nullptr);
    Vector::FileScope scope(void) const { return cmScope; }
    VectorData data(void) const { return mData; }
    VectorData & data(void) { return mData; }
//    UnitFloatVector coefVector(void) const
//    { return mCoefVector; }

signals:
    void openCancelled(Vector::FileScope scope);
    void opened(Vector::FileScope scope,
                VectorObject * vector);
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
//    UnitFloatVector mCoefVector;
};

