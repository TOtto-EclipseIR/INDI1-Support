#include "VectorTableModel.h"

#include <QModelIndex>
#include <QTimer>

#include "Debug.h"
#include "VectorObject.h"


VectorTableModel::VectorTableModel(const int rows, QObject * parent)
    : QAbstractTableModel(parent)
    , mMatrix(VariantMatrix::Size(rows,
                  VectorObject::columnCount()))
{
    TRACEQFI << mMatrix.rowCount() << mMatrix.colCount();
    setObjectName("VectorTableModel");
    emit ctorFinished(this);
}

int VectorTableModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return mMatrix.rowCount();
}

int VectorTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return mMatrix.colCount();
}

QVariant VectorTableModel::data(const QModelIndex & mx,
                                const int role) const
{
    Q_UNUSED(role)
    QVariant result = mMatrix.value(
                VariantMatrix::Index(mx.row(), mx.column()));
    TRACEQFI << "return :" << mx.row() << mx.column() << result;
    return result;
}

void VectorTableModel::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, &VectorTableModel::setup);
}

void VectorTableModel::setup(void)
{
    TRACEFN()
    // QModelIndex mx00 = createIndex(0, 0);
    QModelIndex mxRoot;
    beginInsertColumns(mxRoot, 0, mMatrix.colCount());
    EXPECT(insertColumns(0, mMatrix.colCount(), mxRoot));
    endInsertColumns();
    beginInsertRows(mxRoot, 0, mMatrix.rowCount());
    EXPECT(insertRows(0, mMatrix.rowCount(), mxRoot));
    endInsertRows();

    setHeaderData(VectorObject::nullColumn,         Qt::Horizontal, "Index");
    setHeaderData(VectorObject::BaseLineCol,        Qt::Horizontal, "Base Line");
    setHeaderData(VectorObject::SubjectOneCol,      Qt::Horizontal, "Subject\nOne");
    setHeaderData(VectorObject::SubjectTwoCol,      Qt::Horizontal, "Subject Two");
    setHeaderData(VectorObject::DeltaBaseOneCol,    Qt::Horizontal, "Delta BaseOne");
    setHeaderData(VectorObject::DeltaBaseTwoCol,    Qt::Horizontal, "Delta BaseTwo");
    setHeaderData(VectorObject::DeltaOneTwoCol,     Qt::Horizontal, "Delta OneTwo");
    setHeaderData(VectorObject::RatioBaseOneCol,    Qt::Horizontal, "Ratio BaseOne");
    setHeaderData(VectorObject::RatioBaseTwoCol,    Qt::Horizontal, "Ratio BaseTwo");
    setHeaderData(VectorObject::RatioOneTwoCol,     Qt::Horizontal, "Ratio OneTwo");
    emit headerDataChanged(Qt::Horizontal,
                           VectorObject::nullColumn,
                           VectorObject::RatioOneTwoCol);
    finishSetup(this);
}

void VectorTableModel::set(const Vector::FileScope scope,
                           UnitFloatVector coefs)
{
    TRACEQFI << Vector::scopeString(scope) << coefs.size()
             << mMatrix.rowCount() << mMatrix.colCount();
    int rows = mMatrix.rowCount();
    coefs.resize(rows);
    TRACE << "coefs.resize()" << coefs.size();
    VariantMatrix::Index ix;
    ix.setCol(int(scope));
    for (int row = 0; row < rows; ++row)
    {
        ix.setRow(row);
//        TRACE << ix.row() << ix.col() << coefs.at(row);
        mMatrix.set(ix, QVariant(coefs.value(row)));
    }
    recalculate(scope);
}

void VectorTableModel::openVectorFile(Vector::FileScope scope,
                                      QString fileName)
{
    TRACEQFI << scope << fileName;
    VectorObject * openVector = new VectorObject(scope, this);
    connect(openVector, &VectorObject::openCancelled,
            mainWindow(), &MainWindow::openDialogCancelled);
    connect(openVector, &VectorObject::opened,
            this, &VectorTableModel::vectorOpened);
    openVector->openFileName(fileName);
}

void VectorTableModel::vectorOpened(VectorObject * newVector)
{
    TRACEQFI << newVector->scope();
    Vector::FileScope scope = newVector->scope();
    VectorObject * oldVector = vector(scope);
    if (oldVector)
    {
        emit closed(scope);
        oldVector->deleteLater();
    }
    set(newVector);
    emit opened(newVector);
}


void VectorTableModel::set(VectorObject * vector)
{
    TRACEQFI << vector->objectName() << vector->vectorSize();
    mVectorMap.insert(vector->scope(), vector);
    set(vector->scope(), vector->coefVector());
}

void VectorTableModel::recalculate(void)
{
    TRACEFN()
    for(int scope = Vector::BaseLine;
        scope < Vector::sizeScope;
        ++scope)
    {
        recalculate(Vector::FileScope(scope));
    }
    for(int column = VectorObject::DeltaBaseOneCol;
        column < VectorObject::sizeColumns;
        ++column)
    {
        recalculate(VectorObject::Columns(column));
    }
}

void VectorTableModel::recalculate(const Vector::FileScope scope)
{
    TRACEQFI << "TODO";
}

void VectorTableModel::recalculate(const VectorObject::Columns column)
{
    TRACEQFI << "TODO";

}
