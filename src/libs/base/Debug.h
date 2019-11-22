// file: ./src/libs/base/Debug.h
#pragma once

#include <QtDebug>

#define TRACE qDebug()
#define TRACEFN() { qDebug() << Q_FUNC_INFO; }
//#define TRACEPCZ(pcz) { QDebug(pcz); }
//#define TRACEQST(qst) { QDebug(qPrintable(qst)); }
