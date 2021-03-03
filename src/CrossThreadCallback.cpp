#include "tp_qt_utils/CrossThreadCallback.h"

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

  //################################################################################################
  Private(CrossThreadCallback* q_, int delay_):
    q(q_),
    delay(delay_)
  {

  }

  //################################################################################################
  void customEvent(QEvent*) final;

  //################################################################################################
  void timerEvent(QTimerEvent*) final;
};

//##################################################################################################
void CrossThreadCallback::Private::customEvent(QEvent*)
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

//##################################################################################################
void CrossThreadCallback::Private::timerEvent(QTimerEvent*)
{
  if(timerID)
  {
    killTimer(timerID);
    timerID=0;
  }

  q->callback();
}

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
  QCoreApplication::postEvent(d, new QEvent(QEvent::User));
}

}
