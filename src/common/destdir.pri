# {/git/eclipseir.com/indi1.support}/src/common/destdir.pri
# QMake DESTDIR definitions

#EIRDEST:
# <qmajv> QT_MAJOR_VERSION
# <spec> QMake Build MKSPEC os: Windows | Linux TBD
# <proc> QMake Build MKSPEC arch:
##          Windows: x86 (32 bit) | x86-64
##          Linux: TBD
# <config> Release 'bin' | Debug 'dbg' | Profile TBD
# <cver> INDI & EIRC Common Version

EIRDEST = D:\INDIface\<config><qmajv><proc>-<spec>-v<cver>

CONFIG(debug, debug|release) {
    EIRDEST = $$replace(EIRDEST, <config>, dbg)
}
else {`
    EIRDEST = $$replace(EIRDEST, <config>, bin)
}

EIRDEST = $$replace(EIRDEST, <qmajv>, $$QT_MAJOR_VERSION)
EIRDEST = $$replace(EIRDEST, <spec>, $$QMAKE_HOST.os)
EIRDEST = $$replace(EIRDEST, <proc>, $$QMAKE_HOST.arch)
EIRDEST = $$replace(EIRDEST, <cver>, $$VERSTRING)

DESTDIR = $$EIRDEST
LIBS += -L$$EIRDEST

#\qtmp\build-util-Desktop_Qt_5_12_3_MinGW_64_bit-Debug
