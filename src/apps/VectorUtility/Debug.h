// file: ./Debug.h
#pragma once

#include <QtDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QPointer>
#include <QTimer>

#define TIME QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
#define DEBUG(qmt, pfx) qmt() << pfx << TIME
#define DEBUGQFI(qmt, pfx) qmt() << pfx << TIME   << Q_FUNC_INFO
#define DEBUGFN(qmt, pfx) { qmt() << pfx << TIME   << Q_FUNC_INFO; }
#define DEBUGPSZ(qmt, pfx, psz) { qmt(pfx << TIME  psz); }
#define DEBUGQST(qmt, pfx, qst) { qmt(pfx << TIME  qPrintable(qst)); }
#define DEBUGDO(qmt, pfx, msg) { qmt() << pfx << TIME  << Q_FUNC_INFO << __LINE__ << "TODO:" << #msg; }
#define DEBUGUSE(qmt, pfx, var)  { (void)(var); qmt() << pfx << TIME   << Q_FUNC_INFO << "TO USE:" << #var; }
#define DEBUGEXP(qmt, pfx, bexpr) { if ( ! bexpr) qmt() << pfx << TIME   << "Expectation FAILED:" << #bexpr; }
#define DEBUGXEQ(qmt, pfx, expt, var) { if (expt != var) qmt() << pfx << TIME  << Q_FUNC_INFO   << "Expectation FAILED:" << #expt << expt << "==" << #var << var; }
#define DEBUGXNE(qmt, pfx, expt, var) { if (expt == var) qmt() << pfx << TIME  << Q_FUNC_INFO   << "Expectation FAILED:" << #expt << expt << "!=" << #var << var; }
#define DEBUGXPTR(qmt, pfx, ptr) { if (nullptr == ptr) qmt() << pfx << TIME  << Q_FUNC_INFO   << "Allocation FAILED:" <<  #ptr; }
#define DEBUGRTN(qmt, pfx, expr) { qmt() << pfx << TIME << Q_FUNC_INFO << "Return:" << #expr; return expr; }
#define DEBUGRTV(qmt, pfx) { qmt() << pfx << TIME << Q_FUNC_INFO << "Return(void)"; return; }
#define DEBUGQUIT { QTimer::singleShot(0, qApp, SLOT(quit())); }

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
#define NEEDRTN(expr)           DEBUGRTN(qCritical, PERROR, expr)
#define NEEDRTV()               DEBUGRTV(qCritical, PERROR)

#define ABORT(strm)             DEBUG(qCritical, PABORT) << strm; DEBUGQUIT
#define ABORTQFI(strm)          DEBUGQFI(qCritical, PABORT) << strm; DEBUGQUIT
#define ABORTFN()               DEBUGFN(qCritical, PABORT); DEBUGQUIT
#define ABORTPSZ(psz)           DEBUGPSZ(qCritical, PABORT, psz); DEBUGQUIT
#define ABORTQST(qst)           DEBUGQST(qCritical, PABORT, qPrintable(qst)); DEBUGQUIT
#define BEXPECT(bexpr)          DEBUGEXP(qCritical, PABORT, bexpr); DEBUGQUIT
#define BEXPECTEQ(expt, var)    DEBUGXEQ(qCritical, PABORT, expt, var); DEBUGQUIT
#define BEXPECTNE(expt, var)    DEBUGXNE(qCritical, PABORT, expt, var); DEBUGQUIT
#define BEXPECTPTR(ptr)         DEBUGXPTR(qCritical, PABORT, ptr); DEBUGQUIT
#define MUSTDO(msg)             DEBUGDO(qCritical, PABORT, msg); DEBUGQUIT
#define MUSTUSE(msg)            DEBUGUSE(qCritical, PABORT, msg); DEBUGQUIT

#define CHKPTR(var) var; BEXPECTNE(nullptr, var)
#define VCHKPTR(var) BEXPECTNE(nullptr, var)
#define CHKALLOC(typ, var, nexpr) typ * var = new nexpr; TSTALLOC(var)
#define TSTALLOC(var) BEXPECTPTR(var)


