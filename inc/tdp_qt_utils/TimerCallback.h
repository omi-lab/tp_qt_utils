#ifndef tdp_qt_utils_TimerCallback_h
#define tdp_qt_utils_TimerCallback_h

#include "tdp_qt_utils/Globals.h"

#include <functional>

class QTimer;

namespace tdp_qt_utils
{

//##################################################################################################
class TDP_QT_UTILS_SHARED_EXPORT TimerCallback
{
  QTimer* m_timer;
public:
  //################################################################################################
  TimerCallback(void* opaque, void (*callback)(void* opaque), int timeOut);

  //################################################################################################
  TimerCallback(const std::function<void()>& callback, int timeOut);

  //################################################################################################
  ~TimerCallback();

  //################################################################################################
  void setTimeOut(int timeOut);

  //################################################################################################
  int timeOut();
};

}

#endif
