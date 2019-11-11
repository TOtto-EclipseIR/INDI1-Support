// file: ./src/libs/exe/DocumentActions.h
#pragma once
#include "Exe.h"

#include <QObject>

#include <QFileInfo>

#include "../core/VariableId.h"
#include "../core/VariableSet.h"

class EXE_EXPORT DocumentActions : public QObject
{
    Q_OBJECT
public:
    explicit DocumentActions(QObject * parent=nullptr);
    void configure(const VariableSet & config,
                   const VariableId & sectionName=VariableId());

public slots:
    void openFilesDialog(QWidget * parent=nullptr);

signals:
    void openFileList(QFileInfoList files);
    void openFilesCancel(void);


private:
    VariableSet mConfig;
    QFileInfoList mOpenFilesList;
};

