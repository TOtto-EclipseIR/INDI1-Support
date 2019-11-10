// file: ./src/libs/base/ErrorStatusObject.h
#pragma once
#include "Base.h"

#include <QObject>

#include <QDomDocument>
#include <QVariant>

class BASE_EXPORT ErrorStatusObject : public QObject
{
    Q_OBJECT
public:
    explicit ErrorStatusObject(QObject * parent=nullptr);
    bool isError(void) const
    { return ! mErrorString.isEmpty(); }
    void clear(void)
    { mErrorString.clear(); }

public slots:
    void setError(QString format, QVariant var1,
                  QVariant var2=QVariant(),
                  QVariant var3=QVariant(),
                  QVariant var4=QVariant());
    void setError(QString message);
    bool tryDomSetContent(QDomDocument * doc,
                          QByteArray ba);

signals:
    void error(QString message);

private:
    QString mDomError;
    int mDomErrLine=0;
    int mDomErrCol=0;
    QString mErrorString;
};

