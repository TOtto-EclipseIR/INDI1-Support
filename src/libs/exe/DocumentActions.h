// file: ./src/libs/exe/DocumentActions.h
#pragma once
#include "Exe.h"

#include <QObject>
class VVMainWindow;

#include <QFileInfo>
#include <QWidget>

#include "../core/VariableId.h"
#include "../core/VariableSet.h"

class EXE_EXPORT DocumentActions : public QObject
{
    Q_OBJECT
public:
    explicit DocumentActions(QObject * parent=nullptr);
    void setParentWidget(QWidget * widget)
    { mpParentWidget = widget; }
    VVMainWindow * main(void)
    { return (VVMainWindow *)(mpParentWidget); }
    void configure(const VariableSet & config,
                   const VariableId & sectionName=VariableId());

public slots:
    void handleFileList(QFileInfoList files);
    void openFilesDialog(void);

signals:
    void dialogOpenFiles(QFileInfoList files);
    void openFilesCancel(void);


private:
    QWidget * mpParentWidget=nullptr;
    VariableSet mConfig;
    QFileInfoList mOpenFilesList;
};

