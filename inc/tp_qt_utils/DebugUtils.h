#ifndef tp_qt_utils_DebugUtils_h
#define tp_qt_utils_DebugUtils_h

#include "tp_qt_utils/Globals.h"

#include "tp_utils/DebugUtils.h"

namespace tp_qt_utils
{

//##################################################################################################
// Functions to manipulate QDebug output.

//##################################################################################################
//! What to include in terminal debug messages. Values may be OR'ed together.
enum QDebugFormat
{
  QDebugFormatTime   = 0x01,  //!< Time with second accuracy
  QDebugFormatTimeMs = 0x03,  //!< Time with millisecond accuracy
  QDebugFormatType   = 0x04   //!< 'D' if debug, 'I' if info, 'W' if warning, 'C' if critical, 'F' if fatal
};

//##################################################################################################
//! Specify what to output in debug messages on the terminal.
/*!
The environment variable QT_MESSAGE_PATTERN may be used to specify the format of Qt debug messages
on the terminal. If set, it takes precedence over this function.

\warning This function will have no effect if the environment variable QT_MESSAGE_PATTERN is set.

\note To override the format set by qDebugToLog(), call this function after qDebugToLog().

\param format - OR of QDebugFormat values
*/
void TP_QT_UTILS_SHARED_EXPORT setQDebugFormat(QDebugFormat format);

//##################################################################################################
//! Writes an entry to a log file
/*!
This will write an entry to a log file, it will truncate the log file when it gets larger than the
maxLength set by qDebugToLog().
*/
bool TP_QT_UTILS_SHARED_EXPORT writeLogEntry(const QString& logPath, QString txt);

//##################################################################################################
//! Write qDebug to a log file
/*!
This installs a qDebug handler that redirects all qDebug, qWarning, etc to a log file.

\param logPath - The path of the file to write to
\param maxLength - The maximum length of the log file, once this is reached the file is truncated.
*/
void TP_QT_UTILS_SHARED_EXPORT qDebugToLog(const QString& logPath, int64_t maxLength=500000);

//##################################################################################################
void TP_QT_UTILS_SHARED_EXPORT setPrefix(const QString& prefix);

//##################################################################################################
QString formatDebugString(QtMsgType type, const QMessageLogContext& context, const QString& msg);
QString formatDebugString(tp_utils::MessageType type, const std::string& msg);

//##################################################################################################
void installMessageHandler(const std::function<void(tp_utils::MessageType, const std::string&)>& callback);

//##################################################################################################
void removeMessageHandler();

//##################################################################################################
void installDefaultMessageHandler();

}

#endif
