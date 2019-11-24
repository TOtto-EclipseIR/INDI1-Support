// file: ./src/libs/base/ErrorStatusObject.cpp
#include "ErrorStatusObject.h"

ErrorStatusObject::ErrorStatusObject(QObject * parent)
    : QObject(parent)
{
    setObjectName("ErrorStatusObject");
}

void ErrorStatusObject::setError(QString format, QVariant var1,             QVariant var2, QVariant var3, QVariant var4)
{
    QString message = format;
    message.replace("%1", var1.toString());
    message.replace("%2", var2.toString());
    message.replace("%3", var3.toString());
    message.replace("%4", var4.toString());
}

void ErrorStatusObject::setError(QString message)
{
    mErrorString = message;
    if (isError()) emit error(message);
}

bool ErrorStatusObject::tryDomSetContent(QDomDocument *doc,
                                         QByteArray ba)
{
    QString error;
    int errLine, errCol;
    bool success = doc->setContent(ba, &error, &errLine, &errCol);
    if ( ! success)
        setError("Error parsing XML at %2,%3: %1",
                 error, errLine, errCol);
    return success;

}
