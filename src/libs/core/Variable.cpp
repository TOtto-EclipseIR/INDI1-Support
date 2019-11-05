#include "Variable.h"

#include <QtXml/QDomElement>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

#include "VariableType.h"

Variable::Variable(void)
{
}

Variable::Variable(const VariableId & id,
                   const QVariant::Type varType) :
    mId(id),
    mCurrentVar(QVariant(varType)),
    mDefaultVar(QVariant(varType))
{
}

Variable::Variable(const VariableId & id,
                   const QVariant defaultValue)
    : mId(id)
    , mCurrentVar(defaultValue)
    , mDefaultVar(defaultValue)
{
}

Variable::Variable(const VariableId & id,
         const QVariant currentValue,
         const QVariant defaultValue)
    : mId(id)
    , mCurrentVar(currentValue)
    , mDefaultVar(defaultValue)
{
}

Variable Variable::fromString(const QString & string)
{
    int x = string.indexOf('=');
    if (x < 0)
        return Variable(VariableId(string), true);
    else
    {
        QString name = string.left(x);
        QString value = string.mid(x+1);
        return Variable(VariableId(name), value);
    }
}

bool Variable::isNull(void) const
{
    if (mId.isNull()) return true;
    if (mDefaultVar.isNull()) return true;
    return false;
}

VariableId Variable::id(void) const
{
    return mId;
}

QVariant Variable::var(void) const
{
    return mCurrentVar;
}

QVariant Variable::defaultVar(void) const
{
    return mDefaultVar;
}


void Variable::reset(void)
{
    mCurrentVar = mDefaultVar;
}

void Variable::clear(void)
{
    mCurrentVar = QVariant(mDefaultVar.type());
}

void Variable::set(const QVariant newValue)
{
    mCurrentVar.setValue(newValue);
}

/*
bool Variable::readXml(const QDomElement & de)
{
    (void)de;
    // TODO
    return false;
}

QDomElement Variable::writeXml(void) const
{
    // TODO
    return QDomElement();
}
*/
