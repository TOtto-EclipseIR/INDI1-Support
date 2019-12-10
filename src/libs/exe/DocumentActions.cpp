#include "DocumentActions.h"

#include <QtDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStringList>

#include "../base/Debug.h"
//#include "../core/VariableSetDocument.h"

DocumentActions::DocumentActions(QObject * parent)
    : QObject(parent)
{
    TRACEFN()
    setObjectName("DocumentActions");
 //   connect(this, SIGNAL(dialogOpenFiles(QFileInfoList)),
   //         main(), SLOT(openAllFiles(QFileInfoList)));
}

void DocumentActions::configure(const VariableSet & config,
                                const VariableId & sectionName)
{
    TRACEFN()
    mConfig = sectionName.isNull()
                ? config
                : config.exportSection(sectionName);
}

void DocumentActions::handleFileList(QFileInfoList files)
{
    TRACEFN()
    foreach (QFileInfo fi, files)
    {
//        vsd->readFile();
//        vsd->parse();
    }

}

void DocumentActions::openFilesDialog(void)
{
    TRACEFN()
    QString caption = mConfig.value("OpenFiles/Caption").toString();
    QString filter = mConfig.value("OpenFiles/Filter").toString();
    static QDir dir = QDir::current();
    TRACE << caption << filter << dir;

    QStringList fileNames =
            QFileDialog::getOpenFileNames(mpParentWidget,
            caption, dir.path(), filter);

    if (fileNames.isEmpty())
    {
        TRACE << "emit openFilesCancel()";
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
        TRACE << "emit dialogOpenFiles()" << mOpenFilesList;
        emit dialogOpenFiles(mOpenFilesList);
    }
}

