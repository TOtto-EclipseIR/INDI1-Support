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
    int capacity(void) const
    { return QVector<T>::capacity(); }
    bool isEmpty(void) const
    { checkCapacity(); return QVector<T>::isEmpty(); }
    void append(const T & t)
    { QVector<T>::append(t); checkCapacity(); }
    void prepend(const T & t)
    { QVector<T>::prepend(t); checkCapacity(); }
    void insert(const int x, const T & t)
    { QVector<T>::insert(x, t); checkCapacity(); }
    QVector<T> mid(const int startIndex, const int length=-1)
    { checkCapacity(); return QVector<T>::mid(startIndex, length); }
    T first(void)
    { return mid(0, 1)[0]; }
    QVector<T> first(const int count)
    { return mid(0, count); }



private:
    void checkCapacity(void) const
    {
#if 0
        int capSize = capacity();
        qDebug() << Q_FUNC_INFO << size() << capSize << mMaxCapacity;
        if (capSize > mMaxCapacity)
            qFatal("QQVector : over capacity");
#endif
    }

private:
    int mMaxCapacity = 4096;
};

