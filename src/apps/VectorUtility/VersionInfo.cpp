#include "VersionInfo.h"

#include "Debug.h"

VersionInfo::VersionInfo(const QString & verString,
                         const unsigned  major,
                         const unsigned  minor,
                         const unsigned  micro,
                         const unsigned  branch,
                         const unsigned build)
    : mString(verString)
    , mMajor(major)
    , mMinor(minor)
    , mMicro(micro)
    , mBranch(branch)
{
    set(build);
    mDateTime = QDateTime::currentDateTimeUtc();
}

void VersionInfo::set(unsigned  major,
                      unsigned  minor,
                      unsigned  micro,
                      unsigned  branch)
{
    mMajor = major, mMinor = minor, mMicro = micro, mBranch = branch;
}

void VersionInfo::set(const QString & verString)
{
    mString = verString;
}

void VersionInfo::set(const unsigned buildNumber)
{
    mMicro &= 0xFF;
    mMicro |= (buildNumber << 8);
}

unsigned VersionInfo::build(void) const
{
    return mMicro >> 8;
}

QString VersionInfo::string(void) const
{
    return mString;
}

QString VersionInfo::toString(void) const
{
    return QString("v%1.%2%3%4%5%6%7%8")
            .arg(mMajor).arg(mMinor, 2, 10, QLatin1Char('0'))
            .arg(release(mMicro & 0xFF))
            .arg(mBranch ? "+" : "").arg(mBranch)
            .arg(build() ? "[" : "").arg(build()).arg(build() ? "]" : "");
}

QString VersionInfo::dotString(void) const
{
    return QString("%1.%2.%3.%4").arg(mMajor).arg(mMinor)
            .arg(mMicro).arg(mBranch);
}

QString VersionInfo::buildDate(const bool localZone,
                               const QString & format) const
{
    QDateTime dt = localZone ? mDateTime.toLocalTime() : mDateTime;
    QString fmt = format.isEmpty() ? "yyyy-mm-dd HH:MM U" : format;
    fmt.replace("U", localZone ? "" : "UTC");
    return mDateTime.toString(fmt);
}

QVector<unsigned short> VersionInfo::WindowsVersion() const
{
    QVector<unsigned short> vervec(4);
    vervec[0] = mMajor, vervec[1] = mMinor,
            vervec[2] = mMicro, vervec[3] = mBranch;
    return vervec;
}

QString VersionInfo::release(const unsigned micro)
{
    if (0 == micro) return "";
    if (micro < 26) return QChar(0x40+micro);
    if (micro < 0xA0) return "?"; TODO("handle");
    if (micro < 0xB0) return "Alpha"+QString::number(micro - 0xA0);
    if (micro < 0xC0) return "Beta"+QString::number(micro - 0xB0);
    if (micro < 0xF0) return "RC"+QString::number(micro - 0xC0);
    return "Final"+QString::number(micro - 0xF0);

}
