#pragma once
#include <QString>
#include <QVariant>

typedef QString VarId;
typedef QVariantMap VarMap; // TODO

class BaseDocument
{

public:
    explicit BaseDocument(void) {}
    QVariant value(const VarId & id);
    void set(const VarId & id, const QVariant & var);
    bool contains(const VarId & id);

private:
    VarMap mVarMap;

};

