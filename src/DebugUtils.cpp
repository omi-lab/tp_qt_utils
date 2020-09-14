#include "tp_qt_utils/DebugUtils.h"
#include "tp_utils/StackTrace.h"
#include "tp_utils/TimeUtils.h"

#include "tp_utils/StackTrace.h"
#include "tp_utils/DebugUtils.h"

#include <QtGlobal>
#include <QTextStream>
#include <QDateTime>
#include <QFile>

#include <iostream>

#ifdef TP_QT_ANDROID
#include <android/log.h>
#endif

namespace
{

//##################################################################################################
int64_t maxLength = 500000;
QString& qDebugLogPath(){static QString s; return s;}
QString& prefix(){static QString s; return s;}

QtMessageHandler originalMessageHandler = nullptr;
void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  QString txt = tp_qt_utils::formatDebugString(type, context, msg);

  if(!qDebugLogPath().isEmpty() && tp_qt_utils::writeLogEntry(qDebugLogPath(), txt))
  {
    if(type==QtFatalMsg)
      abort();
  }
  else
  {
    QByteArray dat = txt.toLatin1();
    std::cout << dat.constData() << std::endl;
  }
}

}

namespace tp_qt_utils
{

//##################################################################################################
void setQDebugFormat(QDebugFormat format)
{
  QString fmt;
  if(format & QDebugFormatTimeMs)
    fmt += "%{time hh:mm:ss.zzz} ";
  else if(format & QDebugFormatTime)
    fmt += "%{time hh:mm:ss} ";
  if(format & QDebugFormatType)
    fmt += "%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}  ";
  fmt += "%{function} %{message}";
  qSetMessagePattern(fmt);
}

//##################################################################################################
bool writeLogEntry(const QString& logPath, QString txt)
{
  QFile outFile(logPath);
  if(!outFile.open(QIODevice::ReadWrite | QIODevice::Append))
    return false;

  txt.prepend(QDateTime::fromMSecsSinceEpoch(tp_utils::currentTime()*Q_INT64_C(1000)).toString("[dd/MM/yy hh:mm:ss.zzz]"));

  int64_t seekTo = outFile.size();
  if(seekTo>maxLength)
  {
    outFile.resize(0);
    {
      QTextStream ts(&outFile);
      ts << txt << endl;
    }
  }
  else
  {
    QTextStream ts(&outFile);
    ts << txt << endl;
  }

  return true;
}

//##################################################################################################
void qDebugToLog(const QString& logPath, int64_t maxLength_)
{
  qDebugLogPath() = logPath;
  maxLength = maxLength_;

  qSetMessagePattern("%{time hh:mm:ss.zzz} %{if-debug}Debug%{endif}%{if-warning}Warning%{endif}%{if-critical}Critical%{endif}%{if-fatal}Fatal%{endif} %{message}");

  originalMessageHandler = qInstallMessageHandler(messageHandler);

  tp_utils::installMessageHandler([](tp_utils::MessageType type, const std::string& message)
  {
    messageHandler((type==tp_utils::MessageType::Debug)?QtDebugMsg:QtWarningMsg,
                   QMessageLogContext(),
                   QString::fromStdString(message));
  });
}

//##################################################################################################
void setPrefix(const QString& prefix)
{
  ::prefix() = prefix;
}

//##################################################################################################
QString formatDebugString(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  TP_UNUSED(context);
  QString txt = prefix();
  switch (type)
  {
  case QtDebugMsg:
    txt += QString("Dbg:%1").arg(msg);
    break;
  case QtWarningMsg:
    txt += QString("Wrn:%1").arg(msg);
    break;
  case QtCriticalMsg:
    txt += QString("Crt:%1").arg(msg);
    break;
  case QtFatalMsg:
    txt += QString("Ftl:%1").arg(msg);
    break;
  default:
    txt += QString("Msg:%1").arg(msg);
    break;
  }

  if(type == QtFatalMsg                                   ||
     QString(msg).contains("ASSERT")                      ||
     QString(msg).contains("exited after QThreadStorage") ||
     QString(msg).contains("destroying locked mutex")       )
    txt.append(QString("\n%1").arg(QString::fromStdString(tp_utils::formatStackTrace())));

  return txt;
}

//##################################################################################################
QString formatDebugString(tp_utils::MessageType type, const std::string& msg)
{
  return formatDebugString(((type==tp_utils::MessageType::Debug)?QtDebugMsg:QtWarningMsg),
                           QMessageLogContext(),
                           QString::fromStdString(msg));
}

namespace
{
std::function<void(tp_utils::MessageType, const std::string&)> combinedMessageHandler_tp;

//##################################################################################################
void combinedMessageHandler_qt(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  TP_UNUSED(context);

  tp_utils::MessageType t = tp_utils::MessageType::Warning;
  if(type == QtDebugMsg)
    t = tp_utils::MessageType::Debug;

  if(combinedMessageHandler_tp)
    combinedMessageHandler_tp(t, msg.toStdString());
}
}

//##################################################################################################
void installMessageHandler(const std::function<void(tp_utils::MessageType, const std::string&)>& callback)
{
  combinedMessageHandler_tp = callback;
  originalMessageHandler = qInstallMessageHandler(combinedMessageHandler_qt);
  tp_utils::installMessageHandler(callback);
}

//##################################################################################################
void removeMessageHandler()
{
  qInstallMessageHandler(originalMessageHandler);
  combinedMessageHandler_tp = std::function<void(tp_utils::MessageType, const std::string&)>();
  tp_utils::installMessageHandler(std::function<void(tp_utils::MessageType, const std::string&)>());
}

//##################################################################################################
//## Platform Abstractions #########################################################################
//##################################################################################################

#ifdef TP_QT_ANDROID
namespace
{
//##################################################################################################
static void messageHandler(QtMsgType messageType,
                           const QMessageLogContext &context,
                           const QString &message)
{
  TP_UNUSED(context);

  const char* tag="qWarning";
  switch(messageType)
  {
  case QtDebugMsg:   tag="qDebug";   break;
  case QtWarningMsg: tag="qWarning"; break;
  default:                           break;
  }

  __android_log_print(ANDROID_LOG_DEBUG, tag, "%s", qPrintable(message));
}
}
#endif

//##################################################################################################
void installDefaultMessageHandler()
{
#ifdef __ANDROID_API__
  qInstallMessageHandler(messageHandler);
#endif

  tp_utils::installDefaultMessageHandler();
}

}
