#ifndef tdp_qt_utils_ProcessStatusManager_h
#define tdp_qt_utils_ProcessStatusManager_h

#include "tdp_qt_utils/Globals.h"
#include "tp_utils/StringID.h"

#include <QString>
#include <QSet>
#include <QList>

namespace tdp_qt_utils
{
//##################################################################################################
enum WarningLevel
{
  WarningLevelUndefined,
  WarningLevelMessage,
  WarningLevelDebug,
  WarningLevelWarning,
  WarningLevelError
};

//##################################################################################################
QString TDP_QT_UTILS_SHARED_EXPORT warningLevelToString(WarningLevel warningLevel);

//##################################################################################################
WarningLevel TDP_QT_UTILS_SHARED_EXPORT warningLevelFromString(const QString& warningString);

//##################################################################################################
struct TDP_QT_UTILS_SHARED_EXPORT ProcessStatusMessage
{
  tp_utils::StringID messageName;
  WarningLevel warningLevel;
  QString message;

  //################################################################################################
  ProcessStatusMessage(const tp_utils::StringID& messageName_, WarningLevel warningLevel_, const QString& message_):
    messageName(messageName_),
    warningLevel(warningLevel_),
    message(message_)
  {

  }

  //################################################################################################
  static QString findMessage(const QList<ProcessStatusMessage>& messages, const tp_utils::StringID& messageName)
  {
    Q_FOREACH(const ProcessStatusMessage& message, messages)
      if(message.messageName == messageName)
        return message.message;
    return QString();
  }
};

//##################################################################################################
QString TDP_QT_UTILS_SHARED_EXPORT serializeProcessStatusMessages(const QList<ProcessStatusMessage>& statusMessages);

//##################################################################################################
QString TDP_QT_UTILS_SHARED_EXPORT serializeProcessStatusMessagesHTML(const QList<ProcessStatusMessage>& statusMessages, const QSet<tp_utils::StringID>& remove=QSet<tp_utils::StringID>());

//##################################################################################################
QList<ProcessStatusMessage> TDP_QT_UTILS_SHARED_EXPORT deserializeProcessStatusMessages(const QString& statusString);

//##################################################################################################
//! A class for recording process status messages.
/*!
This is a common class for recording process status messages. Each message is identified by its name
and owner identifier. The messages are not ordered, and there can only be one message at any one
time for a given owner/name combination.

In the context of the HTL web service this class adds and removes server status messages. These are
displayed in the Server Details web page for the server. The message warning level sets the status
colour for the server in the Server Overview web page, as follows:
 - WarningLevelError: red.
 - WarningLevelWarning: yellow.
 - Other warning levels: green.
*/
class TDP_QT_UTILS_SHARED_EXPORT ProcessStatusManager
{
  ProcessStatusManager()=default;
  virtual ~ProcessStatusManager()=default;
public:

  //################################################################################################
  //! Create a process status message.
  /*!
  \param owner   - Identifier for use if clearMessages() is called, or null.
  \param message - Specifies message name, text and warning level.
  */
  static void setMessage(void* owner, const ProcessStatusMessage& message);

  //################################################################################################
  //! Remove process status messages from the list.
  /*!
  This removes a specified message, or all messages, for a given owner identifier.

  \param owner   - Message identifier used in setMessage().
  \param message - Message name to remove, or empty to remove all messages for \p owner.
  */
  static void clearMessages(void* owner, const tp_utils::StringID& messageName=tp_utils::StringID());

  //################################################################################################
  //! Return a list of all process status messages.
  /*!
  \return  List of messages, in no particular order.
  */
  static QList<ProcessStatusMessage> messages();
};

}

#endif
