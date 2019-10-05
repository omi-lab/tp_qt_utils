#ifndef tp_qt_utils_SerialMessage_h
#define tp_qt_utils_SerialMessage_h

#include "tp_qt_utils/Globals.h"

#include <QByteArray>
#include <QDebug>

namespace tp_qt_utils
{

//##################################################################################################
struct tp_qt_UTILS_SHARED_EXPORT SerialMessage
{
  char command;
  QByteArray data;

  SerialMessage(char command_=0, const QByteArray& data_=QByteArray()):
    command(command_),
    data(data_)
  {

  }
};

//##################################################################################################
QDebug tp_qt_UTILS_SHARED_EXPORT operator<<(QDebug d, const SerialMessage& serialMessage);

}

#endif
