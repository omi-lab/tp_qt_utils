TARGET = tp_qt_utils
TEMPLATE = lib

DEFINES += TP_QT_UTILS_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_qt_utils/Globals.h

SOURCES += src/Progress.cpp
HEADERS += inc/tp_qt_utils/Progress.h

SOURCES += src/ExplicitStringIDManager.cpp
HEADERS += inc/tp_qt_utils/ExplicitStringIDManager.h

SOURCES += src/Serialization.cpp
HEADERS += inc/tp_qt_utils/Serialization.h

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

SOURCES += src/ProcessStatusManager.cpp
HEADERS += inc/tp_qt_utils/ProcessStatusManager.h

SOURCES += src/CrossThreadCallback.cpp
HEADERS += inc/tp_qt_utils/CrossThreadCallback.h

SOURCES += src/FormatNumbers.cpp
HEADERS += inc/tp_qt_utils/FormatNumbers.h

SOURCES += src/FormatXML.cpp
HEADERS += inc/tp_qt_utils/FormatXML.h

SOURCES += src/SignalHandler.cpp
HEADERS += inc/tp_qt_utils/SignalHandler.h

SOURCES += src/SerialMessage.cpp
HEADERS += inc/tp_qt_utils/SerialMessage.h

SOURCES += src/EventLatency.cpp
HEADERS += inc/tp_qt_utils/EventLatency.h

