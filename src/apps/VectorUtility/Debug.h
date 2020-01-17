// file: ./Debug.h
#pragma once

#include <QtDebug>
#include <QDateTime>
#include <QPointer>

#define TIME QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
#define DEBUG(qmt, pfx) qmt() << pfx << TIME
#define DEBUGQFI(qmt, pfx) qmt() << pfx << TIME   << Q_FUNC_INFO
#define DEBUGFN(qmt, pfx) { qmt() << pfx << TIME   << Q_FUNC_INFO; }
#define DEBUGPSZ(qmt, pfx, psz) { qmt(pfx << TIME  psz); }
#define DEBUGQST(qmt, pfx, qst) { qmt(pfx << TIME  qPrintable(qst)); }
#define DEBUGDO(qmt, pfx, msg) { qmt() << pfx << TIME  << Q_FUNC_INFO << "TODO:" << #msg; }
#define DEBUGUSE(qmt, pfx, var)  { (void)(var); qmt() << pfx << TIME   << Q_FUNC_INFO << "TO USE:" << #var; }
#define DEBUGEXP(qmt, pfx, bexpr) { if ( ! bexpr) qmt() << pfx << TIME   << "Expectation FAILED:" << #bexpr; }
#define DEBUGXEQ(qmt, pfx, expt, var) { if (expt != var) qmt() << pfx << TIME   << "Expectation FAILED:" << #expt << expt << "==" << #var << var; }
#define DEBUGXNE(qmt, pfx, expt, var) { if (expt == var) qmt() << pfx << TIME   << "Expectation FAILED:" << #expt << expt << "!=" << #var << var; }
#define DEBUGXPTR(qmt, pfx, ptr) { if (nullptr == ptr) qmt() << pfx << TIME   << "Allocation FAILED:" <<  #ptr; }

#define PINFO   "=INFO "
#define PTRACE  "-TRACE"
#define PWARN   "*WARN "
#define PERROR  "#ERROR"
#define PABORT  "@ABORT"

#define INFO                    DEBUG(qInfo, PINFO) // << stuff
#define INFOQFI                 DEBUGQFI(qInfo, PINFO) // << stuff
#define INFOFN()                DEBUGFN(qInfo, PINFO);
#define INFOPSZ(psz)            DEBUGPSZ(qInfo, PINFO, psz);
#define INFOQST(qst)            DEBUGQST(qInfo, PINFO, qPrintable(qst));
#define NEXPECT(bexpr)          DEBUGEXP(qInfo, PINFO, bexpr)
#define NEXPECTEQ(expt, var)    DEBUGXEQ(qInfo, PINFO, expt, var)
#define NEXPECTNE(expt, var)    DEBUGXNE(qInfo, PINFO, expt, var)

#define TRACE                   DEBUG(qDebug, PTRACE) // << stuff
#define TRACEQFI                DEBUGQFI(qDebug, PTRACE) // << stuff
#define TRACEFN()               DEBUGFN(qDebug, PTRACE);
#define TRACEPSZ(psz)           DEBUGPSZ(qDebug, PTRACE, psz);
#define TRACEQST(qst)           DEBUGQST(qDebug, PTRACE, qPrintable(qst));
#define TEXPECT(bexpr)          DEBUGEXP(qDebug, PTRACE, bexpr)
#define TEXPECTEQ(expt, var)    DEBUGXEQ(qDebug, PTRACE, expt, var)
#define TEXPECTNE(expt, var)    DEBUGXNE(qDebug, PTRACE, expt, var)
#define TODO(msg)               DEBUGDO(qDebug, PTRACE, msg)
#define TOUSE(msg)              DEBUGDOUSE(qDebug, PTRACE, msg)
#define UNUSED(var)             Q_UNUSED(var)

#define WARN                    DEBUG(qWarning, PWARN) // << stuff
#define WARNQFI                 DEBUGQFI(qWarning, PWARN) // << stuff
#define WARNFN()                DEBUGFN(qWarning, PWARN);
#define WARNPSZ(psz)            DEBUGPSZ(qWarning, PWARN, psz);
#define WARNQST(qst)            DEBUGQST(qWarning, PWARN, qPrintable(qst));
#define WEXPECT(bexpr)          DEBUGEXP(qWarning, PWARN, bexpr)
#define WEXPECTEQ(expt, var)    DEBUGXEQ(qWarning, PWARN, expt, var)
#define WEXPECTNE(expt, var)    DEBUGXNE(qWarning, PWARN, expt, var)
#define WANTDO(msg)             DEBUGDO(qWarning, PWARN, msg)
#define WANTUSE(msg)            DEBUGUSE(qWarning, PWARN, msg)

#define ERROR                   DEBUG(qCritical, PERROR) // << stuff
#define ERRORQFI                DEBUGQFI(qCritical, PERROR) // << stuff
#define ERRORFN()               DEBUGFN(qCritical, PERROR);
#define ERRORPSZ(psz)           DEBUGPSZ(qCritical, PERROR, psz);
#define ERRORQST(qst)           DEBUGQST(qCritical, PERROR, qPrintable(qst));
#define EXPECT(bexpr)           DEBUGEXP(qCritical, PERROR, bexpr)
#define EXPECTEQ(expt, var)     DEBUGXEQ(qCritical, PERROR, expt, var)
#define EXPECTNE(expt, var)     DEBUGXNE(qCritical, PERROR, expt, var)
#define NEEDDO(msg)             DEBUGDO(qCritical, PERROR, msg)
#define NEEDUSE(msg)            DEBUGUSE(qCritical, PERROR, msg)

#define ABORT(strm)             DEBUG(qCritical, PABORT) << strm; Q_ASSERT_X(false, "Expectation", "Exit")
#define ABORTQFI(strm)          DEBUGQFI(qCritical, PABORT) << strm; Q_ASSERT_X(false, "Expectation", "Exit")
#define ABORTFN()               DEBUGFN(qCritical, PABORT); Q_ASSERT_X(false, "Expectation", "Exit")
#define ABORTPSZ(psz)           DEBUGPSZ(qCritical, PABORT, psz); Q_ASSERT_X(false, "Expectation", "Exit")
#define ABORTQST(qst)           DEBUGQST(qCritical, PABORT, qPrintable(qst)); Q_ASSERT_X(false, "Expectation", "Exit")
#define BEXPECT(bexpr)          DEBUGEXP(qCritical, PABORT, bexpr); Q_ASSERT_X( ! bexpr, "Expectation", "Exit")
#define BEXPECTEQ(expt, var)    DEBUGXEQ(qCritical, PABORT, expt, var); Q_ASSERT_X(expt != var, "Expectation", "Exit")
#define BEXPECTNE(expt, var)    DEBUGXNE(qCritical, PABORT, expt, var); Q_ASSERT_X(expt != var, "Expectation", "Exit")
#define BEXPECTPTR(ptr)         DEBUGXPTR(qCritical, PABORT, ptr); Q_ASSERT_X(nullptr != ptr, "Allocation", "Exit");
#define MUSTDO(msg)             DEBUGDO(qCritical, PABORT, msg); Q_ASSERT_X(false, "Expectation", "Exit")
#define MUSTUSE(msg)            DEBUGUSE(qCritical, PABORT, msg); Q_ASSERT_X(false, "Expectation", "Exit")

#define CHKPTR(var) var; BEXPECTNE(nullptr, var)
#define VCHKPTR(var) BEXPECTNE(nullptr, var)
#define CHKALLOC(typ, var, nexpr) typ * var = new nexpr; TSTALLOC(var)
#define TSTALLOC(var) BEXPECTPTR(var)


