// file: ./src/libs/base/FunctionInfo.h
#pragma once
#include "Base.h"

#include <QSharedDataPointer>

class FunctionInfoData;

class BASE_EXPORT FunctionInfo
{
public:
    FunctionInfo();
    FunctionInfo(const FunctionInfo &);
    FunctionInfo &operator=(const FunctionInfo &);
    ~FunctionInfo();

private:
    QSharedDataPointer<FunctionInfoData> data;
};

