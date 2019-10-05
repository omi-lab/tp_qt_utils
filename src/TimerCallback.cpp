#include "tp_qt_utils/TimerCallback.h"

#include <QTimer>

namespace tp_qt_utils
{

//##################################################################################################
TimerCallback::TimerCallback(const std::function<void()>& callback, int64_t timeOutMS):
  tp_utils::AbstractTimerCallback(callback, timeOutMS),
  m_timer(new QTimer())
{
  QObject::connect(m_timer, &QTimer::timeout, callback);
  m_timer->start(int(timeOutMS));
}

//##################################################################################################
TimerCallback::~TimerCallback()
{
  delete m_timer;
}

//##################################################################################################
void TimerCallback::setTimeOutMS(int64_t timeOutMS)
{
  m_timer->setInterval(int(timeOutMS));
}

}
