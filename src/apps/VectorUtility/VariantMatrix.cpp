#include "VariantMatrix.h"

#include "Debug.h"

VariantMatrix::VariantMatrix(void) {}

VariantMatrix::VariantMatrix(const VariantMatrix::Size size,
                             const QVariant &fillValue)
{
    fill(size, fillValue);
}

void VariantMatrix::fill(const VariantMatrix::Size size,
                         const QVariant & fillValue)
{
    mValues.clear();
    mSize = mReserved = size;
    mValues.fill(fillValue, size.count());
}

VariantMatrix::Size VariantMatrix::size() const
{
    return mSize;
}

void VariantMatrix::set(const VariantMatrix::Index ix,
                        const QVariant value)
{
    mValues.replace(ix.index(size()), value);
}

QVariant VariantMatrix::value(const VariantMatrix::Index ix) const
{
    return mValues.value(ix.index(size()));
}

int VariantMatrix::rowCount() const
{
    return size().rows();
}

int VariantMatrix::colCount() const
{
    return size().cols();
}



VariantMatrix::Size::Size(void)
{
    first = 0, second = 0;
}

VariantMatrix::Size::Size(const int rows, const int cols)
{
    first = rows, second = cols;
}

int VariantMatrix::Size::rows() const
{
    return first;
}

int VariantMatrix::Size::cols() const
{
    return second;
}

int VariantMatrix::Size::count() const
{
    return  first * second;
}


VariantMatrix::Index::Index()
{
    first = second = 0;
}

VariantMatrix::Index::Index(const int row, const int col)
{
    first = row, second = col;
}

void VariantMatrix::Index::setRow(const int row)
{
    first = row;
}

void VariantMatrix::Index::setCol(const int col)
{
    second = col;
}

int VariantMatrix::Index::row() const
{
    return first;
}

int VariantMatrix::Index::col() const
{
    return second;
}

int &VariantMatrix::Index::row()
{
    return first;
}

int &VariantMatrix::Index::col()
{
    return second;
}

int VariantMatrix::Index::index(const VariantMatrix::Size size) const
{
#if 1
    return row() * size.cols() + col();
#else
    TRACEQFI << first << second << size.rows() << size.cols();
    int result = row() * size.cols() + col();
    TRACEQFI << "return :" << result;
    return result;
#endif
}
