#include "BasicId.h"

#include "../base/BaseIdBehavior.h"

class CORE_EXPORT BasicIdBehavior : public BaseIdBehavior
{
public:
    static BasicIdBehavior * instance(void)
    {
        if ( ! singleton)
            singleton = new BasicIdBehavior;
        return singleton;
    }
    virtual ~BasicIdBehavior() {}

private:
    BasicIdBehavior(void)
        : BaseIdBehavior("/", "/" + lower + upper
                                  + number + fileSymbol)
    {
    }

    static BasicIdBehavior * singleton;
};

BasicIdBehavior * BasicIdBehavior::singleton=nullptr;

BasicId::BasicId(const QString & inString)
    : AbstractIdString(BasicIdBehavior::instance(), inString)
{
}

BasicId::BasicId(const char * chars)
    : AbstractIdString(BasicIdBehavior::instance(), QString(chars))
{
}

BasicId::BasicId(const char * chars,
                       const char * chars1,
                       const char * chars2,
                       const char * chars3)
    : AbstractIdString(BasicIdBehavior::instance())
{
    set(QString(chars));
    append(QString(chars1));
    append(QString(chars2));
    append(QString(chars3));
}
