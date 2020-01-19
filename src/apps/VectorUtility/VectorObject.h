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
    enum Columns
    {
        nullColumn          = 0,
        BaseLineCol         = 0x01000001,
        SubjectOneCol       = 0x01000002,
        SubjectTwoCol       = 0x01000003,
        DeltaBaseOneCol     = 0x13000004,
        DeltaBaseTwoCol     = 0x15000005,
        DeltaOneTwoCol      = 0x16000006,
        RatioBaseOneCol     = 0x23000007,
        RatioBaseTwoCol     = 0x25000008,
        RatioOneTwoCol      = 0x26000009,
        sizeColumns,
        ColMaskIndex        = 0x000000FF,
        ColMaskBaseLine     = 0x01000000,
        ColMaskSubjectOne   = 0x02000000,
        ColMaskSubjectTwo   = 0x04000000,
        ColMaskDelta        = 0x10000000,
        ColMaskRatio        = 0x20000000,
    };
    Q_ENUM(Columns);
    typedef QList<Columns> ColumnList;

public:
    explicit VectorObject(const Vector::FileScope scope,
                           QObject * parent=nullptr);
    Vector::FileScope scope(void) const
    { return cmScope; }
    QString scopeString(void) const
    { return Vector::scopeString(cmScope); }
    VectorData data(void) const { return mData; }
    VectorData & data(void) { return mData; }
    int vectorSize(void) const { return mCoefVector.size(); }
    UnitFloatVector coefVector(void) const
    { return mCoefVector; }
    bool isValid(int index) const
    { return (index >= 0) && (index < mCoefVector.size()) ; }
    UnitFloat::Value & at(const int x)
    { Q_ASSERT(isValid(x)); return mCoefVector[x]; }
    UnitFloat::Value value(const int x) const
    { return isValid(x) ? mCoefVector.value(x) : UnitFloat::Value(); }

public: // static
    static int columnCount(void)
    { return sizeColumns & ColMaskIndex; }
//    static VectorObject * vector(const Vector::FileScope scope)
  //  { return mVectors[scope] ; }
    static void set(VectorObject * vector);

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
//    QFileInfo mFileInfo;
    VectorData mData;
    UnitFloatVector mCoefVector;
    static QHash<Vector::FileScope, VectorObject *> mVectors;
};
