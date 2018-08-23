#ifndef tdp_qt_utils_SerialMessage_h
#define tdp_qt_utils_SerialMessage_h

#include "tdp_qt_utils/Globals.h"

#include <QByteArray>
#include <QDebug>

namespace tdp_qt_utils
{

//##################################################################################################
struct TDP_QT_UTILS_SHARED_EXPORT SerialMessage
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
QDebug TDP_QT_UTILS_SHARED_EXPORT operator<<(QDebug d, const SerialMessage& serialMessage);

}

#endif
