#include "tdp_qt_utils/TimerCallback.h"

#include <QTimer>

namespace tdp_qt_utils
{

//##################################################################################################
TimerCallback::TimerCallback(void* opaque, void (*callback)(void* opaque), int timeOut):
  m_timer(new QTimer())
{
  QObject::connect(m_timer, &QTimer::timeout, [opaque, callback](){callback(opaque);});
  m_timer->start(timeOut);
}

//##################################################################################################
TimerCallback::TimerCallback(const std::function<void()>& callback, int timeOut):
  m_timer(new QTimer())
{
  QObject::connect(m_timer, &QTimer::timeout, callback);
  m_timer->start(timeOut);
}

//##################################################################################################
TimerCallback::~TimerCallback()
{
  delete m_timer;
}

//##################################################################################################
void TimerCallback::setTimeOut(int timeOut)
{
  m_timer->setInterval(timeOut);
}

//##################################################################################################
int TimerCallback::timeOut()
{
  return m_timer->interval();
}

}
