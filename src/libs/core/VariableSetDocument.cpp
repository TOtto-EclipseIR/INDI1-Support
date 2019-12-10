#include "VariableSetDocument.h"

DEFINE_DATAPROPS(VariableSetDocument, VariableSetDocumentData)

void VariableSetDocument::ctor(void) {}
void VariableSetDocument::dtor() {} // ditto dtor

VariableSetDocument::VariableSetDocument(VariableSet * pVarSet)
    : mpVariableSet(pVarSet)
{
    ctor();
}

void VariableSetDocument::close()
{
    if (mpTextStream)
    {
        delete mpTextStream;
        mpTextStream = nullptr;
    }
    if (mpDataStream)
    {
        delete mpDataStream;
        mpDataStream = nullptr;
    }
    if (mpBuffer)
    {
        delete mpBuffer;
        mpBuffer = nullptr;
    }
    if (mpFile)
    {
        delete mpFile;
        mpFile = nullptr;
    }
}

bool VariableSetDocument::read(const QFileInfo & fi)
{
    mpFile = new QFile(fi.absoluteFilePath());
    mpFile->open(QIODevice::ReadOnly);
    QByteArray ba = mpFile->readAll();
    mpBuffer = new QBuffer(&ba);
    return mpFile->isReadable() && 0 != mpBuffer->size();
}

bool VariableSetDocument::write(const QFileInfo & fi)
{

    return false;
}

bool VariableSetDocument::parse(void)
{

    return false;
}

bool VariableSetDocument::parseImage(void)
{


    return false;
}

bool VariableSetDocument::parseDomDocument(void)
{
    if (0 == mpBuffer->size()) return false;
    return parseDomDocument(mpBuffer->buffer());
}

bool VariableSetDocument::parseDomDocument(const QByteArray & bytes)
{


    return false;
}
