TARGET = tp_qt_utils
TEMPLATE = lib

DEFINES += TP_QT_UTILS_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_qt_utils/Globals.h

SOURCES += src/FileUtils.cpp
HEADERS += inc/tp_qt_utils/FileUtils.h

SOURCES += src/DebugUtils.cpp
HEADERS += inc/tp_qt_utils/DebugUtils.h

SOURCES += src/ValidationUtils.cpp
HEADERS += inc/tp_qt_utils/ValidationUtils.h

SOURCES += src/BinaryUtils.cpp
HEADERS += inc/tp_qt_utils/BinaryUtils.h

SOURCES += src/EventDebug.cpp
HEADERS += inc/tp_qt_utils/EventDebug.h

SOURCES += src/TimeUtils.cpp
HEADERS += inc/tp_qt_utils/TimeUtils.h

SOURCES += src/TimerCallback.cpp
HEADERS += inc/tp_qt_utils/TimerCallback.h

SOURCES += src/CrossThreadCallback.cpp
HEADERS += inc/tp_qt_utils/CrossThreadCallback.h

SOURCES += src/FormatXML.cpp
HEADERS += inc/tp_qt_utils/FormatXML.h

SOURCES += src/EventLatency.cpp
HEADERS += inc/tp_qt_utils/EventLatency.h

SOURCES += src/Throttler.cpp
HEADERS += inc/tp_qt_utils/Throttler.h
