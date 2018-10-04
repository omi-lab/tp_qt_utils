#include "tdp_qt_utils/CrossThreadCallback.h"

#include <QCoreApplication>

namespace tdp_qt_utils
{
//##################################################################################################
struct CrossThreadCallback::Private: public QObject
{
  CrossThreadCallback* q;

  //################################################################################################
  Private(CrossThreadCallback* q_):
    q(q_)
  {

  }

  //################################################################################################
  void customEvent(QEvent*) final;
};

//##################################################################################################
void CrossThreadCallback::Private::customEvent(QEvent*)
{
  q->callback();
}

//##################################################################################################
CrossThreadCallback::CrossThreadCallback(const std::function<void()>& callback):
  tp_utils::AbstractCrossThreadCallback(callback),
  d(new Private(this))
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
  QCoreApplication::postEvent(d,new QEvent(QEvent::User));
}

}
