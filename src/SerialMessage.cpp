#include "tp_qt_utils/SerialMessage.h"

#include "tp_qt_utils/BinaryUtils.h"

namespace tp_qt_utils
{

//##################################################################################################
QDebug operator<<(QDebug d, const SerialMessage& serialMessage)
{
  d.noquote().nospace() << "Command: " << serialMessage.command << " data: " << tp_qt_utils::binaryDebug(serialMessage.data);
  return d.resetFormat();
}

}
