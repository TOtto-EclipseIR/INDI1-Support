#pragma once

#include <QPair>
#include <QPoint>
#include <QSize>
#include <QVariant>
#include <QVector>

class VariantMatrix
{
public:
    typedef QVector<QVariant> QVariantVector;

    class Size : private QPair<int, int>
    {
    public:
        Size(void);
        Size(const int rows, const int cols);
        void set(const int rows, const int cols);
        int rows(void) const;
        int cols(void) const;
        int count(void) const;
    };

    class Index : private QPair<int, int>
    {
    public:
        Index(void);
        Index(const int row, const int col);
        void set(const int row, const int col);
        void setRow(const int row);
        void setCol(const int col);
        int row(void) const;
        int col(void) const;
        int & row(void);
        int & col(void);
        int index(const Size size) const;
    };

public:
    VariantMatrix(void);
    VariantMatrix(const Size size,
                  const QVariant & fillValue=QVariant());
    void fill(const Size size,
              const QVariant & fillValue);
    void fill(const QVariant & fillValue=QVariant());
    void resize(const Size size);
    void clear(void);
    bool isEmpty(void) const;
    bool isValid(const Index index) const;
    Size size(void) const;
    int count(void) const;
    void set(const Index index, const QVariant value);
    QVariant & at(const Index index);
    QVariant value(const Index index) const;
    int rowCount(void) const;
    int colCount(void) const;
    void setRow(int row, QVariantVector values);
    void setCol(int col, QVariantVector values);


private:
    QVariantVector mValues;
    Size mSize;
    Size mReserved;
    int mRowShift = 0;
};

