#include "tdp_qt_utils/ProcessStatusManager.h"

#include "tp_utils/MutexUtils.h"

#include <QMap>

namespace tdp_qt_utils
{
namespace
{
struct PrivateState_lt
{
  TPMutex mutex{TPM};
  QHash<void*, QHash<tp_utils::StringID, ProcessStatusMessage>> messages;
};

PrivateState_lt& privateState()
{
  static PrivateState_lt privateState;
  return privateState;
}


}

//##################################################################################################
QString warningLevelToString(WarningLevel warningLevel)
{
  switch(warningLevel)
  {
  case WarningLevelUndefined: return "undefined";
  case WarningLevelMessage:   return "message";
  case WarningLevelDebug:     return "debug";
  case WarningLevelWarning:   return "warning";
  case WarningLevelError:     return "error";
  }

  return "unknown";
}

//##################################################################################################
namespace
{
struct WarningLevelStrings_lt
{
  const QMap<QString, WarningLevel> warningLevelStrings;
  WarningLevelStrings_lt():
    warningLevelStrings{{"undefined", WarningLevelUndefined},
                        {"message",   WarningLevelMessage},
                        {"debug",     WarningLevelDebug},
                        {"warning",   WarningLevelWarning},
                        {"error",     WarningLevelError}}
  {
  }
};
}

//##################################################################################################
WarningLevel warningLevelFromString(const QString& warningString)
{
  static WarningLevelStrings_lt s;
  return s.warningLevelStrings.value(warningString, WarningLevelUndefined);
}

//##################################################################################################
QString serializeProcessStatusMessages(const QList<ProcessStatusMessage>& statusMessages)
{
  static const QString pattern("%1:%2:%3\n");
  QString serialized;

  Q_FOREACH(const ProcessStatusMessage& message, statusMessages)
    serialized.append(pattern.arg(QString::fromStdString(message.messageName.keyString()),
                                  tdp_qt_utils::warningLevelToString(message.warningLevel),
                                  QString(message.message.toLatin1().toBase64())));

  return serialized;
}

//##################################################################################################
QString serializeProcessStatusMessagesHTML(const QList<ProcessStatusMessage>& statusMessages, const QSet<tp_utils::StringID>& remove)
{
  static const QString pattern("%1:%2:%3\n");
  QString serialized;

  QHash<tp_utils::StringID, const ProcessStatusMessage*> statusMessageMap;

  Q_FOREACH(const ProcessStatusMessage& message, statusMessages)
    statusMessageMap.insert(message.messageName, &message);

  QList<tp_utils::StringID> keys = statusMessageMap.keys();
  std::sort(keys.begin(), keys.end(), tp_utils::lessThanStringID);

  Q_FOREACH(const tp_utils::StringID& key, keys)
  {
    const ProcessStatusMessage& message = *statusMessageMap.value(key);

    if(remove.contains(message.messageName))
      continue;

    QString html = message.message.toHtmlEscaped();

    html.replace(':', QString("&#58"));
    html.replace('\n', QString("<br>"));

    serialized.append(pattern.arg(
                        QString::fromStdString(message.messageName.keyString()),
                        tdp_qt_utils::warningLevelToString(message.warningLevel),
                        html));
  }

  return serialized;
}

//##################################################################################################
QList<ProcessStatusMessage> deserializeProcessStatusMessages(const QString& statusString)
{
  QList<ProcessStatusMessage> statusMessages;
  QStringList lines = statusString.split('\n');

  Q_FOREACH(const QString& line, lines)
  {
    QStringList parts = line.split(':');
    if(parts.size()!=3)
      continue;

    QByteArray message = QByteArray::fromBase64(parts.at(2).toLatin1());
    statusMessages.append(ProcessStatusMessage(parts.at(0).toStdString(),
                                               warningLevelFromString(parts.at(1)),
                                               QString::fromLatin1(message)));
  }

  return statusMessages;
}

//##################################################################################################
void ProcessStatusManager::setMessage(void* owner, const ProcessStatusMessage& message)
{
  PrivateState_lt& ps = privateState();
  ps.mutex.lock(TPM);
  ps.messages[owner].insert(message.messageName, message);
  ps.mutex.unlock(TPM);
}

//##################################################################################################
void ProcessStatusManager::clearMessages(void* owner, const tp_utils::StringID& messageName)
{
  PrivateState_lt& ps = privateState();
  ps.mutex.lock(TPM);
  if(messageName.isValid())
    ps.messages[owner].remove(messageName);
  else
    ps.messages.remove(owner);
  ps.mutex.unlock(TPM);
}

//##################################################################################################
QList<ProcessStatusMessage> ProcessStatusManager::messages()
{
  QList<ProcessStatusMessage> messages;
  PrivateState_lt& ps = privateState();

  ps.mutex.lock(TPM);
  QHashIterator<void*, QHash<tp_utils::StringID, ProcessStatusMessage>> i(ps.messages);
  while(i.hasNext())
  {
    i.next();
    Q_FOREACH(const ProcessStatusMessage& message, i.value())
      messages.append(message);
  }
  ps.mutex.unlock(TPM);

  return messages;
}
}
