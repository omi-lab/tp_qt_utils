#include "tp_qt_utils/CrossThreadCallback.h"

#include "tp_utils/RefCount.h"
#include "tp_utils/MutexUtils.h" // IWYU pragma: keep

#include <QCoreApplication>

namespace tp_qt_utils
{
//##################################################################################################
struct CrossThreadCallback::Private: public QObject
{
  TP_REF_COUNT_OBJECTS("tp_qt_utils::CrossThreadCallback::Private");
  TP_NONCOPYABLE(Private);

  CrossThreadCallback* q;
  int delay;
  int timerID{0};

  // Kludge to get arround false positives caused by QCoreApplication::postEvent in thread sanitizer.
#ifdef TP_SANITIZE_THREAD
  TPMutex mutex{TPM};
  int pollTimerID{startTimer(10)};
  int triggered{0};
#endif

  //################################################################################################
  Private(CrossThreadCallback* q_, int delay_):
    q(q_),
    delay(delay_)
  {
  }

  //################################################################################################
  void customEvent(QEvent*) override
  {
    if(delay>=0)
    {
      if(timerID==0)
        timerID=startTimer(delay);
    }
    else
    {
      q->callback();
    }
  }

  //################################################################################################
  void timerEvent(QTimerEvent* timerEvent) override
  {
#ifdef TP_SANITIZE_THREAD
    if(pollTimerID == timerEvent->timerId())
    {
      TP_MUTEX_LOCKER(mutex);
      while(triggered>0)
      {
        triggered--;
        TP_MUTEX_UNLOCKER(mutex);
        customEvent(nullptr);
      }
      return;
    }
#else
    TP_UNUSED(timerEvent);
#endif

    if(timerID)
    {
      killTimer(timerID);
      timerID=0;
    }

    q->callback();
  }
};

//##################################################################################################
CrossThreadCallback::CrossThreadCallback(const std::function<void()>& callback, int delay):
  tp_utils::AbstractCrossThreadCallback(callback),
  d(new Private(this, delay))
{

}

//##################################################################################################
CrossThreadCallback::CrossThreadCallback(const std::function<void()>& callback):
  tp_utils::AbstractCrossThreadCallback(callback),
  d(new Private(this, -1))
{

}

//##################################################################################################
CrossThreadCallback::~CrossThreadCallback()
{
  delete d;
}

//##################################################################################################
void CrossThreadCallback::call()
{
#ifdef TP_SANITIZE_THREAD
  d->mutex.locked([&]{d->triggered++;});
#else
  QCoreApplication::postEvent(d, new QEvent(QEvent::User));
#endif
}

}
