#pragma once

#include <QDateTime>
#include <QString>
#include <QVector>

class VersionInfo
{
public:
    VersionInfo(const QString & verString,
                const unsigned  major,
                const unsigned  minor,
                const unsigned  micro,
                const unsigned  branch=0,
                const unsigned build=0);
    void set(const unsigned  major,
             const unsigned  minor,
             const unsigned  micro,
             const unsigned  branch=0);
    void set(const QString & verString);
    void set(const unsigned buildNumber);
    unsigned build(void) const;
    QString string(void) const;
    QString toString(void) const;
    QString dotString(void) const;
    QString buildDate(const bool localZone=true,
                      const QString & format=QString()) const;
    QVector<unsigned short> WindowsVersion(void) const;

private:
    static QString release(const unsigned micro);

private:
    QString mString;
    unsigned mMajor;
    unsigned mMinor;
    unsigned mMicro;
    unsigned mBranch;
    QDateTime mDateTime;
};

