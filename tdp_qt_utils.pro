TARGET = tdp_qt_utils
TEMPLATE = lib

DEFINES += TDP_QT_UTILS_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tdp_qt_utils/Globals.h

SOURCES += src/Progress.cpp
HEADERS += inc/tdp_qt_utils/Progress.h

SOURCES += src/ExplicitStringIDManager.cpp
HEADERS += inc/tdp_qt_utils/ExplicitStringIDManager.h

SOURCES += src/Serialization.cpp
HEADERS += inc/tdp_qt_utils/Serialization.h

SOURCES += src/Interface.cpp
HEADERS += inc/tdp_qt_utils/Interface.h

SOURCES += src/FileUtils.cpp
HEADERS += inc/tdp_qt_utils/FileUtils.h

SOURCES += src/DebugUtils.cpp
HEADERS += inc/tdp_qt_utils/DebugUtils.h

SOURCES += src/ValidationUtils.cpp
HEADERS += inc/tdp_qt_utils/ValidationUtils.h

SOURCES += src/BinaryUtils.cpp
HEADERS += inc/tdp_qt_utils/BinaryUtils.h

SOURCES += src/CallbackThread.cpp
HEADERS += inc/tdp_qt_utils/CallbackThread.h

SOURCES += src/EventDebug.cpp
HEADERS += inc/tdp_qt_utils/EventDebug.h

SOURCES += src/TimeUtils.cpp
HEADERS += inc/tdp_qt_utils/TimeUtils.h

SOURCES += src/TimerCallback.cpp
HEADERS += inc/tdp_qt_utils/TimerCallback.h

SOURCES += src/ProcessStatusManager.cpp
HEADERS += inc/tdp_qt_utils/ProcessStatusManager.h

SOURCES += src/CrossThreadCallback.cpp
HEADERS += inc/tdp_qt_utils/CrossThreadCallback.h

SOURCES += src/FormatNumbers.cpp
HEADERS += inc/tdp_qt_utils/FormatNumbers.h

SOURCES += src/FormatXML.cpp
HEADERS += inc/tdp_qt_utils/FormatXML.h

SOURCES += src/SignalHandler.cpp
HEADERS += inc/tdp_qt_utils/SignalHandler.h

SOURCES += src/SerialMessage.cpp
HEADERS += inc/tdp_qt_utils/SerialMessage.h

include(../tdp_build/qmake/project_qt.pri)
