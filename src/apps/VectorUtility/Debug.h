// file: ./Debug.h
#pragma once

#include <QtDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QPointer>
#include <QTimer>

#define TIME QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
#define DEBUG(qmt, pfx) qmt() << pfx << TIME << __LINE__
#define DEBUGQFI(qmt, pfx) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__
#define DEBUGFN(qmt, pfx) { qmt() << pfx << TIME   << Q_FUNC_INFO << __LINE__; }
#define DEBUGPSZ(qmt, pfx, psz) { qmt(pfx << TIME  << __LINE__ psz); }
#define DEBUGQST(qmt, pfx, qst) { qmt(pfx << TIME << __LINE__  qPrintable(qst)); }
#define DEBUGDO(qmt, pfx, msg) { qmt() << pfx << TIME  << Q_FUNC_INFO << __LINE__ << "TODO:" << #msg; }
#define DEBUGUSE(qmt, pfx, var)  { (void)(var); qmt() << pfx << TIME   << Q_FUNC_INFO << __LINE__ << "TO USE:" << #var; }
#define DEBUGEXP(qmt, pfx, bexpr) { if ( ! bexpr) qmt() << pfx << TIME << __LINE__  << "Expectation FAILED:" << #bexpr; }
#define DEBUGXN(qmt, pfx, bexpr) { if (bexpr) qmt() << pfx << TIME << __LINE__  << "Expectation FAILED:" << #bexpr; }
#define DEBUGXEQ(qmt, pfx, expt, var) { if (expt != var) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Expectation FAILED:" << #expt << expt << "==" << #var << var; }
#define DEBUGXNE(qmt, pfx, expt, var) { if (expt == var) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Expectation FAILED:" << #expt << expt << "!=" << #var << var; }
#define DEBUGXPTR(qmt, pfx, ptr) if (nullptr == ptr) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Pointer FAILED:" <<  #ptr;
#define DEBUGPTR(qmt, pfx, ptr, expr)     if (ptr) ptr->expr else DEBUG(qmt, pfx) "Pointer" << #ptr << "FAILED for" << #expr;
#define DEBUGRTN(qmt, pfx, expr) { qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Return:" << #expr; return expr; }
#define DEBUGRTV(qmt, pfx) { qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Return(void)"; return; }
//#define DEBUGQUIT { qCritical() << ""; QTimer::singleShot(0, qApp, SLOT(quit())); }
#define DEBUGQUIT Q_ASSERT(false);
#define DEBUGCON(qmt, pfx, src, sig, rec, slt) TSTALLOC(src); TSTALLOC(rec); if ( ! connect(src,sig,rec,slt)) DEBUG(qmt, pfx) << "Connect FAILED:" << #src << #sig << #rec << #slt;

#define PINFO   "=INFO>"
#define PTRACE  "-TRACE"
#define PWARN   "*WARN>"
#define PERROR  "#ERROR"
#define PABORT  "@FATAL"

#define INFO                    DEBUG(qInfo, PINFO) // << stuff
#define INFOQFI                 DEBUGQFI(qInfo, PINFO) // << stuff
#define INFOFN()                DEBUGFN(qInfo, PINFO);
#define INFOPSZ(psz)            DEBUGPSZ(qInfo, PINFO, psz);
#define INFOQST(qst)            DEBUGQST(qInfo, PINFO, qPrintable(qst));
#define NEXPECT(bexpr)          DEBUGEXP(qInfo, PINFO, bexpr)
#define NEXPECTEQ(expt, var)    DEBUGXEQ(qInfo, PINFO, expt, var)
#define NEXPECTNE(expt, var)    DEBUGXNE(qInfo, PINFO, expt, var)
#define LIKEDO(msg)             DEBUGDO(qInfo, PINFO, msg)

#define TRACE                   DEBUG(qDebug, PTRACE) // << stuff
#define TRACEQFI                DEBUGQFI(qDebug, PTRACE) // << stuff
#define TRACEFN()               DEBUGFN(qDebug, PTRACE);
#define TRACEPSZ(psz)           DEBUGPSZ(qDebug, PTRACE, psz);
#define TRACEQST(qst)           DEBUGQST(qDebug, PTRACE, qPrintable(qst));
#define TEXPECT(bexpr)          DEBUGEXP(qDebug, PTRACE, bexpr)
#define TEXPECTEQ(expt, var)    DEBUGXEQ(qDebug, PTRACE, expt, var)
#define TEXPECTNE(expt, var)    DEBUGXNE(qDebug, PTRACE, expt, var)
#define TRACERTV()              DEBUGRTV(qDebug, PTRACE)
#define TRACERTN(expr)          DEBUGRTN(qDebug, PTRACE, expr)
#define TODO(msg)               DEBUGDO(qDebug, PTRACE, msg)
#define TOUSE(msg)              DEBUGDOUSE(qDebug, PTRACE, msg)
#define UNUSED(var)             Q_UNUSED(var)

#define WARN                    DEBUG(qWarning, PWARN) // << stuff
#define WARNQFI                 DEBUGQFI(qWarning, PWARN) // << stuff
#define WARNFN()                DEBUGFN(qWarning, PWARN);
#define WARNPSZ(psz)            DEBUGPSZ(qWarning, PWARN, psz);
#define WARNQST(qst)            DEBUGQST(qWarning, PWARN, qPrintable(qst));
#define WEXPECT(bexpr)          DEBUGEXP(qWarning, PWARN, bexpr)
//#define WCONNECT(src, sig, dst, slt) { TSTALLOC(src); TSTALLOC(dst); WEXPECT(connect(src, sig, dst, slt)); }
#define WCONNECT(src, sig, dst, slt)    DEBUGCON(qWarning,  PWARN, src, sig, dst, slt)
#define WEXPECTNOT(bexpr)       DEBUGXN(qWarning, PWARN, bexpr)
#define WEXPECTEQ(expt, var)    DEBUGXEQ(qWarning, PWARN, expt, var)
#define WEXPECTNE(expt, var)    DEBUGXNE(qWarning, PWARN, expt, var)
#define WANTDO(msg)             DEBUGDO(qWarning, PWARN, msg)
#define WANTUSE(msg)            DEBUGUSE(qWarning, PWARN, msg)
#define WPTR(ptr, expr)         DEBUGPTR(qWarning, PWARN)

#define ERROR                   DEBUG(qCritical, PERROR) // << stuff
#define ERRORQFI                DEBUGQFI(qCritical, PERROR) // << stuff
#define ERRORFN()               DEBUGFN(qCritical, PERROR);
#define ERRORPSZ(psz)           DEBUGPSZ(qCritical, PERROR, psz);
#define ERRORQST(qst)           DEBUGQST(qCritical, PERROR, qPrintable(qst));
#define EXPECT(bexpr)           DEBUGEXP(qCritical, PERROR, bexpr)
#define EXPECTNOT(bexpr)        DEBUGXN(qCritical, PERROR, bexpr)
#define EXPECTEQ(expt, var)     DEBUGXEQ(qCritical, PERROR, expt, var)
#define EXPECTNE(expt, var)     DEBUGXNE(qCritical, PERROR, expt, var)
//#define CONNECT(src, sig, dst, slt) { TSTALLOC(src); TSTALLOC(dst); EXPECT(connect(src, sig, dst, slt)); }
#define CONNECT(src, sig, dst, slt)    DEBUGCON(qCritical,  PERROR, src, sig, dst, slt)
#define NEEDDO(msg)             DEBUGDO(qCritical, PERROR, msg)
#define NEEDUSE(msg)            DEBUGUSE(qCritical, PERROR, msg)
#define NEEDRTN(expr)           DEBUGRTN(qCritical, PERROR, expr)
#define NEEDRTV()               DEBUGRTV(qCritical, PERROR)
#define PTR(ptr, expr)          DEBUGPTR(qCritical, PERROR)

#define ABORT(strm)             DEBUG(qCritical, PABORT) << strm; DEBUGQUIT
#define ABORTQFI(strm)          DEBUGQFI(qCritical, PABORT) << strm; DEBUGQUIT
#define ABORTFN()               DEBUGFN(qCritical, PABORT); DEBUGQUIT
#define ABORTPSZ(psz)           DEBUGPSZ(qCritical, PABORT, psz); DEBUGQUIT
#define ABORTQST(qst)           DEBUGQST(qCritical, PABORT, qPrintable(qst)); DEBUGQUIT
#define BEXPECT(bexpr)          DEBUGEXP(qCritical, PABORT, bexpr); DEBUGQUIT
//#define BCONNECT(src, sig, dst, slt) { TSTALLOC(src); TSTALLOC(dst); BEXPECT(connect(src, sig, dst, slt)); }
#define BCONNECT(src, sig, dst, slt)    DEBUGCON(qCritical,  PERROR, src, sig, dst, slt); DEBUGQUIT
#define BEXPECTNOT(bexpr)       DEBUGXN(qCritical, PABORT, bexpr); DEBUGQUIT
#define BEXPECTEQ(expt, var)    DEBUGXEQ(qCritical, PABORT, expt, var); DEBUGQUIT
#define BEXPECTNE(expt, var)    DEBUGXNE(qCritical, PABORT, expt, var); DEBUGQUIT
#define BEXPECTPTR(ptr)         DEBUGXPTR(qCritical, PABORT, ptr); DEBUGQUIT
#define MUSTDO(msg)             DEBUGDO(qCritical, PABORT, msg); DEBUGQUIT
#define MUSTUSE(msg)            DEBUGUSE(qCritical, PABORT, msg); DEBUGQUIT

#define TSTALLOC(ptr)           DEBUGXPTR(qCritical, PABORT, ptr);
#define TRYALLOC(typ, var, nexpr) typ * var = new nexpr; TSTALLOC(var)


