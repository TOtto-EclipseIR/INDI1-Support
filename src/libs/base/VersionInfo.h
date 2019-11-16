/*! @file   VersionInfo.h   VersionInfo class
*
*/
#pragma once
#include "Base.h"

#include <QDate>
#include <QSharedData>
#include <QString>

#include "DataProperty.h"

#define SETVERSION() setVersion(VersionInfo(VER_MAJOR, VER_MINOR,           \
                                            VER_BRANCH, VER_RELEASE,        \
                                            VER_STRING, VER_COPYRIGHT,      \
                                            VER_ORGNAME, VER_APPNAME))

// stupid preprocessor tricks follow
#define DEFSTRING2(PDEF) #PDEF
#define DEFSTRING(DEF) DEFSTRING2(DEF)



#define LOGITEM_DATAPROPS(TND) \
    TND(quint64, TimeStamp, 0) \
    TND(int, Level, 0) \

class LogItemData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(LOGITEM_DATAPROPS)
public:
    LogItemData(void)
    {
        DEFINE_DATAPROPS_CTORS(LOGITEM_DATAPROPS)
    }
};

class BASE_EXPORT LogItem
{
    DECLARE_PARENT_DATAPROPS(LOGITEM_DATAPROPS)
    DECLARE_DATAPROPS(LogItem, LogItemData)
    LogItem(const int size); // alternate ctor
};
/*
#define VERSIONINFO_PROPERTIES(TND) \
        TND(QString,    String,        QString()) \
        TND(QString,    OrgName,       QString()) \
        TND(QString,    AppName,       QString()) \
        TND(QString,    Copyright,     QString()) \
        TND(quint8,     Major,         0) \
        TND(quint8,     Minor,         0) \
        TND(quint8,     Branch,        0) \
        TND(quint8,     Release,       0) \

class BASE_EXPORT VersionInfo
{
    DECLARE_PROPERTIES(VERSIONINFO_PROPERTIES);

public:
    VersionInfo(void);
    VersionInfo(const unsigned char major,
                const unsigned char minor,
                const unsigned char branch,
                const unsigned char release,
                const QString & string,
                const QString & copyright,
                const QString & orgname,
                const QString & appname);

    bool isNull(void) const;
    void setVersion(const QString & string);
    void addNotice(const QString & string);
    void setDateTime(const QString & string);
    QString toString(const bool withHex=false) const;
    QString dottedString(void) const;
    quint32 toDWord(void) const;
    QString notice(void) const;
    QStringList noticeList(void) const;
    QString dateTimeString(void) const;
    void check(quint32 key) const;

private:
    QString noti_s;
    QString dt_s;
};

*/
