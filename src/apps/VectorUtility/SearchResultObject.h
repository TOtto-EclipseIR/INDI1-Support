// file: SearchResultObject.h
#pragma once

#include <QObject>

#include <QChar>
#include <QDir>
#include <QList>
#include <QImage>
#include <QMap>
#include <QString>
#include <QStringList>

class SearchResultObject : public QObject
{
    Q_OBJECT
public:
    typedef QList<QDir> QDirList;

public:
    explicit SearchResultObject(const QDir & dir,
                                QObject * parent=nullptr);

public slots:
    void createMatrix(void);

protected:
    void openDir(void);
    void makeMatrixImage(void);
    void writeMatrix(void);

    QImage loadImage(const QString & fileName,
                     const QDir & dir=QDir());
    int score(const QString & baseFileName);
    QChar tier(const QString & baseFileName);
    QList<int> scores(const QStringList & fileNames);
    QList<QChar> tierList(const QList<int> scos);
    void paintMatchBar(QImage * image,
                       const int score,
                       const QColor &color);
    void paintMatchBar(QImage * image,
                       const QString & baseDirName);

signals:
    void matrixImageWritten(QString pathName);

private:
    QDir mDir;
    QDirList mTopDirList;
    QStringList mSubjectFileNames;
    QMap<QString, QStringList> mTopDirFileNamesMap;
    QMap<QString, QList<int> > mTopDirScoreList;
    QMap<QString, QList<QChar> > mTopDirTierList;
    QMap<QString, QImage> mFileNameImageMap;
    QImage mMatrixImage;
    QString mMatrixFilePath;
    static QList<QPoint> smPosOrgins;
};

