// file: ./src/libs/core/VaribleId.h
#pragma once
#include "Core.h"

#include "../base/AbstractIdString.h"

class CORE_EXPORT VariableId : public AbstractIdString
{
public:
    VariableId(const QString & inString=QString());
    VariableId(const char * chars);
    VariableId(const char * chars,
               const char * chars1,
               const char * chars2=nullptr,
               const char * chars3=nullptr);
    VariableId(const VariableId & prefix,
               const char * suffix);
};

