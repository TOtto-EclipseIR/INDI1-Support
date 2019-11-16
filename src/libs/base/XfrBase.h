// file: ./src/libs/base/XfrBase.h
#pragma once
#include "Base.h"

#include "Singleton.h"

#include <QtDebug>
#include <QDateTime>
#include <QMessageLogContext>
#include <QString>

class XfrBase : public Singleton
{
public:
    class Message
    {
    public:
        Message(const QtMsgType msgType,
                const QMessageLogContext & context,
                const QString & msg)
            : mCurrentEpochMsec(QDateTime
                                ::currentMSecsSinceEpoch())
            , mMsgType(msgType)
            , mMessage(msg)
        {
            mContext = copyContextFrom(context);
        }

    private:
        qint64 mCurrentEpochMsec;
        QtMsgType mMsgType;
        QMessageLogContext mContext;
        QString mMessage;
    };

private:
    XfrBase(void) {}
};



