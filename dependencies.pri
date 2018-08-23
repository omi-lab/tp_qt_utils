QT += core

include(../tp_utils/dependencies.pri)

!equals(TARGET, "tdp_qt_utils") {
  LIBS += -ltdp_qt_utils

  #The QT_ARCH variable is poorly documented so I'm not sure if this is the correct.
  # cd toolchains/Qtxxx/xxx/gcc_64/mkspecs/
  # grep -r QT_ARCH
  #Looks like it could be one of the following:
  # arm i386 x64 x86_64 mips
  contains(QT_ARCH, mips) {
    LIBS += -lubacktrace
  }
}
else{
  QT -= gui
}

INCLUDEPATH  += $$PWD/../tdp_qt_utils/inc/
