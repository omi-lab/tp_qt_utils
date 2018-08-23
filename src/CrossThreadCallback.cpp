#include "tdp_qt_utils/CrossThreadCallback.h"

#include <QCoreApplication>

namespace tdp_qt_utils
{
//##################################################################################################
struct CrossThreadCallback::Private: public QObject
{
  std::function<void()> callback;

  //################################################################################################
  Private(std::function<void()> callback_):
    callback(std::move(callback_))
  {

  }

  //################################################################################################
  void customEvent(QEvent*) final;
};

//##################################################################################################
void CrossThreadCallback::Private::customEvent(QEvent*)
{
  callback();
}

//##################################################################################################
CrossThreadCallback::CrossThreadCallback(const std::function<void()>& callback):
  d(new Private(callback))
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
