#pragma once

#include <QtDebug>
#include <QVector>

template <typename T> class QQVector : public QVector<T>
{
public:
    QQVector(void) {}
    void setMaxCapacity(const int n)
    { mMaxCapacity = n; }
    int size(void) const
    { checkCapacity(); return QVector<T>::size(); }
    bool isEmpty(void) const
    { checkCapacity(); return QVector<T>::isEmpty(); }
    void append(const T & t)
    { QVector<T>::append(t); checkCapacity(); }
    void prepend(const T & t)
    { QVector<T>::prepend(t); checkCapacity(); }
    void insert(const int x, const T & t)
    { QVector<T>::insert(x, t); checkCapacity(); }


private:
    void checkCapacity(void) const
    { if (QVector<T>::capacity() < mMaxCapacity)
            qFatal("QQVector : over capacity"); }

private:
    int mMaxCapacity = 4096;
};

