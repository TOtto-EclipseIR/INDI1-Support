#pragma once

#include <QVector>

#include <QColor>

#include "BaseColorSet.h"
#include "UnitFloat.h"
#include "UnitFloatVector.h"
#include "Vector.h"
class VectorObject;


class VectorColumn
{
public:
    typedef qreal Value;
    typedef QVector<Value> ValueVector;

    enum Role
    {
        nullRole            = 0,
        BaseLineRole        = 0x01000001,
        SubjectOneRole      = 0x01000002,
        SubjectTwoRole      = 0x01000003,
        DeltaBaseOneRole    = 0x13000004,
        DeltaBaseTwoRole    = 0x15000005,
        DeltaOneTwoRole     = 0x16000006,
        RatioBaseOneRole    = 0x23000007,
        RatioBaseTwoRole    = 0x25000008,
        RatioOneTwoRole     = 0x26000009,
        sizeRole,
        RoleMaskIndex       = 0x000000FF,
        RoleMaskBaseLine    = 0x01000000,
        RoleMaskSubjectOne  = 0x02000000,
        RoleMaskSubjectTwo  = 0x04000000,
        RoleMaskDelta       = 0x10000000,
        RoleMaskRatio       = 0x20000000,
    };
    typedef QList<Role> RoleList;


public:
    VectorColumn(void);
    VectorColumn(const Role roleIndex, const int rows);
    VectorColumn(const Role roleIndex,
                 const UnitFloatVector & values);
    void clear(void);
    void set(const VectorColumn & other);
    void set(ValueVector values);
    void set(UnitFloatVector ufv);
    void set(VectorObject * vector);
    void set(const ForeBackGroundColors &fbgc);
    bool isEmpty(void) const;
    bool isValid(void) const;
    ValueVector values(void) const
    { return mValues; }
    ValueVector & values(void)
    { return mValues; }
    Role role(void) const
    { return  cmRole; }
    int roleIndex(void) const
    { return cmRole & RoleMaskIndex; }
    QString roleString(void) const;
    int rows(void) const
    { return cmRows; }
    bool operator ==(const VectorColumn & other);
    bool operator < (const VectorColumn & other)
    { return roleIndex() < other.roleIndex(); }
    void operator = (const VectorColumn & other)
    { set(other); }
    QColor baseBackgroundColor(void) const
    { return  mBaseColors.second; }

public: // static
    static int roleCount(void)
    { return sizeRole & RoleMaskIndex; }
    static QString roleString(const int roleIndex);


private:
    const Role cmRole;
    const int cmRows;
    const Value cmInvalid;
    ForeBackGroundColors mBaseColors;
    ValueVector mValues;

private: // static
};

