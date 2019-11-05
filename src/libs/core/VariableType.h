#ifndef VARIABLETYPEBEHAVIOR_H
#define VARIABLETYPEBEHAVIOR_H
#include "Core.h"

#include <QMap>
#include <QMetaType>
#include <QVariant>
#include <QString>
#include <QStringList>

class QDomElement;
class QVariant;

class CORE_EXPORT VariableType
{
protected:
    VariableType(QMetaType::Type varType,
                         const QString & partNames=QString());
    virtual ~VariableType() {}

public:
    static VariableType * behavior(const QMetaType::Type metaType);
    QMetaType::Type metaType(void) const;
    virtual int csvColumns(void) const;
    virtual int csvParts(void) const;
    virtual QString csvHeader(void) const;
    virtual QString csvString(const QVariant & var) const;

private:
    QMetaType::Type mVarType;
    QStringList mNameParts;
    static QMap<QMetaType::Type, VariableType *> mTypeBehaviorMap;
};

#endif // VARIABLETYPEBEHAVIOR_H
