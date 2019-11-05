#include "VariableId.h"
#include "../Base/BaseIdBehavior.h"

class CORE_EXPORT VariableIdBehavior : public BaseIdBehavior
{
public:
    static VariableIdBehavior * instance(void)
    {
        if ( ! singleton)
            singleton = new VariableIdBehavior;
        return singleton;
    }


private:
    VariableIdBehavior(void)
        : BaseIdBehavior("/", "/" + lower + upper + number)
    {
        replace("_", "/");
    }
    virtual ~VariableIdBehavior() {}

    static VariableIdBehavior * singleton;
};

VariableIdBehavior * VariableIdBehavior::singleton=nullptr;

VariableId::VariableId(const QString & inString)
    : AbstractIdString(VariableIdBehavior::instance(), inString)
{
}

VariableId::VariableId(const char * chars)
    : AbstractIdString(VariableIdBehavior::instance(), QString(chars))
{
}

VariableId::VariableId(const char * chars,
                       const char * chars1,
                       const char * chars2,
                       const char * chars3)
    : AbstractIdString(VariableIdBehavior::instance())
{
    set(QString(chars));
    append(QString(chars1));
    append(QString(chars2));
    append(QString(chars3));
}

VariableId::VariableId(const VariableId & prefix,
                       const char * suffix)
    : AbstractIdString(VariableIdBehavior::instance(),
                       prefix)
{
    append(QString(suffix));
}
