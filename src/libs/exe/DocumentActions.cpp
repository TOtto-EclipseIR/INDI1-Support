#include "DocumentActions.h"

#include <QtDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStringList>

DocumentActions::DocumentActions(QObject * parent)
    : QObject(parent)
{
    setObjectName("DocumentActions");
    connect(this, SIGNAL(openFiles(QFileInfoList)),
            this, SLOT(handleFileList(QFileInfoList)));
}

void DocumentActions::configure(const VariableSet & config,
                                const VariableId & sectionName)
{
    mConfig = sectionName.isNull()
                ? config
                : config.exportSection(sectionName);
}

void DocumentActions::openFilesDialog(QWidget * parent)
{
    qDebug() << Q_FUNC_INFO;
    QString caption = mConfig.value("OpenFiles/Caption").toString();
    QString filter = mConfig.value("OpenFiles/Filter").toString();
    static QDir dir = QDir::current();
    qDebug() << caption << filter << dir;

    QStringList fileNames = QFileDialog::getOpenFileNames(parent,
            caption, dir.path(), filter);

    if (fileNames.isEmpty())
    {
        qDebug() << "emit openFilesCancel()";
        emit openFilesCancel();
    }
    else
    {
        foreach (QString fileName, fileNames)
        {
            QFileInfo fi(fileName);
            mOpenFilesList.append(fi);
        }
        dir = mOpenFilesList.first().dir();
        qDebug() << "emit openFileList()" << mOpenFilesList;
        emit openFileList(mOpenFilesList);
    }
}

