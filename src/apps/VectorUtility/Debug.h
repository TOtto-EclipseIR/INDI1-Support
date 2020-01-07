// file: ./Debug.h
#pragma once

#include <QtDebug>

#define TRACE qDebug()
#define TRACEQFI qDebug() << Q_FUNC_INFO
#define TRACEFN() { qDebug() << Q_FUNC_INFO; }
#define TRACEPSZ(psz) { qDebug(psz); }
#define TRACEQST(qst) { qDebug(qPrintable(qst)); }

