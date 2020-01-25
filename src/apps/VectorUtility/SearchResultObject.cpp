// file: SearchResultObject.cpp
#include "SearchResultObject.h"

#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QTimer>

#include "Debug.h"

QList<QPoint> SearchResultObject::smPosOrgins = QList<QPoint>()
    << QPoint(0, 0) << QPoint(128, 0) << QPoint(256, 0)
    << QPoint(384, 0) << QPoint(384, 128) << QPoint(384, 256)
    << QPoint(384, 384) << QPoint(256, 384) << QPoint(128, 384)
    << QPoint(0, 384) << QPoint(0, 256) << QPoint(0, 128);

SearchResultObject::SearchResultObject(const QDir & dir,
                                       QObject * parent)
    : QObject(parent)
    , mDir(dir)
{
    TRACEQFI << dir.absolutePath();
    setObjectName("SearchResultObject");
}

void SearchResultObject::createMatrix()
{
    TRACEFN()

    openDir();
    makeMatrixImage();
    writeMatrix();

    TRACERTV()
    emit matrixImageWritten(mMatrixFilePath);
}

void SearchResultObject::openDir(void)
{
    TRACEQFI << mDir.absolutePath();
    static QStringList dirFileFilter = QStringList() << "R??M*";
    static QStringList subjectFileFilter = QStringList() << "*.PNG" << "*.JPG";

    QStringList topDirNameList = mDir.entryList(dirFileFilter,
                            QDir::Dirs, QDir::Name);
    foreach (QString topDirName, topDirNameList)
        mTopDirList << QDir(topDirName);
    TRACE << topDirNameList;

    mSubjectFileNames = mDir.entryList(subjectFileFilter);
    mSubjectFileNames.removeAll("Matrix.PNG");
    TRACE << mSubjectFileNames;

    foreach (QDir fileDir, mTopDirList)
    {
        QDir rankDir = mDir;
        rankDir.cd(fileDir.path());
        QStringList fileNameList = rankDir.entryList(QDir::Files,
                                                     QDir::Name);
        TRACE << rankDir.absolutePath() << fileNameList;
        mTopDirFileNamesMap.insert(fileDir.path(), fileNameList);
        mTopDirScoreList.insert(fileDir.path(), scores(fileNameList));
        mTopDirTierList.insert(fileDir.path(),
                               tierList(scores(fileNameList)));
    }
    TRACERTV()
}

void SearchResultObject::makeMatrixImage(void)
{
    TRACEFN()
    QImage matrix(QSize(512, 512), QImage::Format_ARGB32);
    QPainter painter(&matrix);

    if ( ! mSubjectFileNames.isEmpty())
    {
        QString firstSubjectImageName = mSubjectFileNames.first();
        QImage subjectImage = loadImage(firstSubjectImageName);
        EXPECTNOT(subjectImage.isNull());
        WEXPECT(subjectImage.save("Subject.PNG"));
        painter.drawImage(QRect(QPoint(128, 128), QSize(256, 256)),
                          subjectImage, subjectImage.rect());
    }

    int nPos = qMin(mTopDirList.size(), 12);
    for (int pos = 0; pos < nPos; ++pos)
    {
        QDir topDir = mTopDirList.at(pos);
        QString firstTopDirFileName
                = mTopDirFileNamesMap.value(topDir.path()).first();
        QImage posImage = loadImage(firstTopDirFileName, topDir);
        WEXPECTNOT(posImage.isNull());
        WEXPECT(posImage.save("Pos"+QString::number(pos)+".PNG"));
        paintMatchBar(&posImage, topDir.path());
        painter.drawImage(QRect(smPosOrgins.at(pos), QSize(128, 128)),
                          posImage, posImage.rect());
    }
    painter.end();

    mMatrixImage = matrix;
    TRACERTV()
}

void SearchResultObject::writeMatrix()
{
    TRACEFN()
    QFileInfo fi(mDir, "Matrix.PNG");
    TRACE << fi;
    WEXPECTNOT(fi.exists());
    mMatrixFilePath = fi.absoluteFilePath();
    WEXPECTNOT(mMatrixImage.isNull());
    WEXPECT(mMatrixImage.save(mMatrixFilePath));
    TRACERTV()
}

QImage SearchResultObject::loadImage(const QString & fileName,
                                     const QDir & dir)
{
    TRACEQFI << fileName;
    QDir imageDir = mDir;
    TRACE << imageDir.absolutePath();
    imageDir.cd(dir.path());
    TRACE << imageDir.absoluteFilePath(fileName);
    QFileInfo fi(imageDir, fileName);
    WEXPECT(fi.exists());
    QImage image(fi.absoluteFilePath());
    WEXPECTNOT(image.isNull())
    TRACE << image.size();
    TRACERTN(image);
}

int SearchResultObject::score(const QString &baseFileName)
{
    QString scoString = baseFileName.mid(4, 3);
    int sco = scoString.toInt();
    TRACEQFI << baseFileName << scoString << sco;
    return sco;
}

QChar SearchResultObject::tier(const QString &baseFileName)
{
    return baseFileName.at(7);
}

QList<int> SearchResultObject::scores(const QStringList & fileNames)
{
    TRACEQFI << fileNames;
    QList<int> scos;
    foreach (QString fn, fileNames) scos << score(fn);
    TRACE << scos;
    return  scos;
}

QList<QChar> SearchResultObject::tierList(const QList<int> scos)
{
    TRACEQFI << scos;
    QList<QChar> chars;
    foreach(int sco, scos)
    {
        if (sco > 850)          chars.append('S');
        else if (sco > 650)     chars.append('P');
        else if (sco > 500)     chars.append('W');
        else                    chars.append('N');
    }
    if (chars.size() >= 2 && 'S' == chars.at(0) && 'S' != chars.at(1))
        chars[0] = 'B';
    TRACE << chars;
    return chars;
}

void SearchResultObject::paintMatchBar(QImage * image,
                                       const int score,
                                       const QColor & color)
{
    TRACEQFI << image->size() << score << color;
    QPainter painter(image);
    int boxHeight = 32;
    QSize imageSize = image->size();
    QRect boxRect(QPoint(0, imageSize.height() - boxHeight),
                  QSize(imageSize.width(), boxHeight));
    QRect barRect(QPoint(boxRect.left() + boxHeight / 2,
                         boxRect.top() + boxHeight / 4),
                  QSize(boxRect.width() - boxHeight,
                        boxHeight / 2));
    QRect scoRect(barRect.topLeft(),
                  QSize(barRect.width() * score / 1000,
                        barRect.height()));
    painter.setBrush(Qt::white), painter.drawRect(boxRect);
    painter.setBrush(Qt::black), painter.drawRect(barRect);
    painter.setBrush(color),     painter.drawRect(scoRect);
    painter.end();
    TRACERTV()
}

#if 0
        QList<QColor>() << QColor()             /* Unknown */
                        << QColor(Qt::yellow)   /* NoMatch */
                        << QColor("#CF0")       /* Weak */
                        << QColor("#FC0")       /* Possible */
                        << QColor(Qt::red)      /* Strong */
                        << QColor(Qt::magenta)  /* Best */
                        << QColor();            /* size */
#endif
void SearchResultObject::paintMatchBar(QImage * image,
                                       const QString & baseDirName)
{
    TRACEQFI << image->size() << baseDirName;
    int sco = score(baseDirName);
    QChar tierChar = tier(baseDirName); // mTopDirTierList.value(baseDirName).at(pos);
    QColor tierColor = Qt::green;
    switch (tierChar.cell())
    {
    case 'N':   tierColor = Qt::yellow;         break;
    case 'W':   tierColor = QColor("#CF0");     break;
    case 'P':   tierColor = QColor("#FC0");     break;
    case 'S':   tierColor = Qt::red;            break;
    case 'B':   tierColor = Qt::magenta;        break;
    default:              ;                     break;
    };
    TRACE << sco << tierChar << tierColor;
    paintMatchBar(image, sco, tierColor);
    TRACERTV()
}
