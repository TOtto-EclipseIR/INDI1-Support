#include "VariableSetDocument.h"

DEFINE_DATAPROPS(VariableSetDocument, VariableSetDocumentData)
void VariableSetDocument::ctor(void) {}
void VariableSetDocument::dtor(void) {} // ditto dtor

VariableSetDocument::VariableSetDocument(VariableSet *pVarSet)
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
