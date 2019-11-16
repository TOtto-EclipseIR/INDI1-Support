#include "FunctionInfo.h"

class FunctionInfoData : public QSharedData
{
public:

};

FunctionInfo::FunctionInfo() : data(new FunctionInfoData)
{

}

FunctionInfo::FunctionInfo(const FunctionInfo &rhs) : data(rhs.data)
{

}

FunctionInfo &FunctionInfo::operator=(const FunctionInfo &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

FunctionInfo::~FunctionInfo()
{

}
