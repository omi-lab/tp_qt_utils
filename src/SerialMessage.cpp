#include "tdp_qt_utils/SerialMessage.h"

#include "tdp_qt_utils/BinaryUtils.h"

namespace tdp_qt_utils
{

//##################################################################################################
QDebug operator<<(QDebug d, const SerialMessage& serialMessage)
{
  d.noquote().nospace() << "Command: " << serialMessage.command << " data: " << tdp_qt_utils::binaryDebug(serialMessage.data);
  return d.resetFormat();
}

}
