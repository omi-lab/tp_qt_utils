#include "tdp_qt_utils/CallbackThread.h"

#include <QTimer>

namespace tdp_qt_utils
{

//##################################################################################################
CallbackThread::CallbackThread(std::function<void(const std::atomic_bool&)> callback, const char* name):
  m_callback(std::move(callback))
{
  setObjectName(name);
}

//##################################################################################################
CallbackThread::~CallbackThread()
{
  m_finish=true;
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
  m_callback(m_finish);
}

}
