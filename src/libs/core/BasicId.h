// File: {support}/src/libs/core/BasicId.h
#pragma once
#include "Core.h"

#include "../Base/AbstractIdString.h"

class CORE_EXPORT BasicId : public AbstractIdString
{
public:
    BasicId(const QString & inString=QString());
    BasicId(const char * chars);
    BasicId(const char * chars,
               const char * chars1,
               const char * chars2=nullptr,
               const char * chars3=nullptr);
};

