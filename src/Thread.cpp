#include <tp_qt_utils/Thread.h>

#include "tp_utils/TimeUtils.h"

namespace tp_qt_utils
{

//################################################################################################
Thread::Thread()
{
  QObject::connect(this, &Thread::finished, this, &QObject::deleteLater);
}

}
