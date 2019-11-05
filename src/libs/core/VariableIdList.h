#ifndef VARIABLEIDLIST_H
#define VARIABLEIDLIST_H
#include "Core.h"

#include <QList>

#include "VariableId.h"


class CORE_EXPORT VariableIdList : public QList<VariableId>
{
public:
    VariableIdList(void);

    operator QStringList(void) const;

};

#endif // VARIABLEIDLIST_H
