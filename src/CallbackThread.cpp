#include "tdp_qt_utils/CallbackThread.h"

#include <QTimer>

namespace tdp_qt_utils
{

//##################################################################################################
CallbackThread::CallbackThread(std::function<void()> callback, const char* name):
  m_callback(std::move(callback))
{
  setObjectName(name);
}

//##################################################################################################
CallbackThread::~CallbackThread()
{
  quit();
  wait();
}

//##################################################################################################
int CallbackThread::exec()
{
  return QThread::exec();
}

//##################################################################################################
void CallbackThread::run()
{
  m_callback();
}

}
