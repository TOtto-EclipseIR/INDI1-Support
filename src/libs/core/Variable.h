#ifndef VARIABLE_H
#define VARIABLE_H
#include "Core.h"


#include <QObject>

#include <QVariant>

//class QDomElement;

#include "VariableId.h"

class CORE_EXPORT Variable
{
public:
    typedef QList<Variable> List;
public:
    explicit Variable(void);
    Variable(const VariableId & id,
             const QVariant::Type varType);
    Variable(const VariableId & id,
             const QVariant defaultValue);
    Variable(const VariableId & id,
             const QVariant currentValue,
             const QVariant defaultValue);
    static Variable fromString(const QString & string);
    bool isNull(void) const;
    VariableId id(void) const;
    QVariant var(void) const;
    QVariant defaultVar(void) const;
    QString typeName(void) const;
    void reset(void);
    void clear(void);
    void set(const QVariant newValue);
    int csvEntryCount(void) const;
    int csvHeadingCount(void) const;
    QString csvEntryString(void) const;
    QString csvEntryHeading(int row) const;

private:
    VariableId mId;
    QVariant mCurrentVar;
    QVariant mDefaultVar;
};

#endif // VARIABLE_H
