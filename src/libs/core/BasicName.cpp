#include "BasicName.h"

#include "../base/BaseIdBehavior.h"

class CORE_EXPORT BasicNameBehavior : public BaseIdBehavior
{
public:
    static BasicNameBehavior * instance(void)
    {
        if ( ! singleton)
            singleton = new BasicNameBehavior;
        return singleton;
    }
    virtual ~BasicNameBehavior() {}

private:
    BasicNameBehavior(void)
        : BaseIdBehavior(QString(), "/" + lower + upper
                                  + number + fileSymbol)
    {
    }

    static BasicNameBehavior * singleton;
};

BasicNameBehavior * BasicNameBehavior::singleton=nullptr;

BasicName::BasicName(const QString & inString)
    : AbstractIdString(BasicNameBehavior::instance(), inString)
{
}

BasicName::BasicName(const char * chars)
    : AbstractIdString(BasicNameBehavior::instance(), QString(chars))
{
}

