// File: {support}/src/libs/core/BasicId.h
#pragma once
#include "Core.h"

#include "../Base/AbstractIdString.h"

class CORE_EXPORT BasicName : public AbstractIdString
{
public:
    BasicName(const QString & inString=QString());
    BasicName(const char * chars);
};
