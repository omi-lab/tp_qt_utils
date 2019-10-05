#ifndef tp_qt_utils_TimerCallback_h
#define tp_qt_utils_TimerCallback_h

#include "tp_qt_utils/Globals.h"

#include "tp_utils/AbstractTimerCallback.h"

#include <functional>

class QTimer;

namespace tp_qt_utils
{

//##################################################################################################
class tp_qt_UTILS_SHARED_EXPORT TimerCallback : public tp_utils::AbstractTimerCallback
{
  QTimer* m_timer;
public:
  //################################################################################################
  TimerCallback(const std::function<void()>& callback, int64_t timeOutMS);

  //################################################################################################
  ~TimerCallback() override;

  //################################################################################################
  void setTimeOutMS(int64_t timeOutMS) override;
};

//##################################################################################################
using TimerCallbackFactory = tp_utils::TimerCallbackFactoryTemplate<TimerCallback>;

}

#endif
