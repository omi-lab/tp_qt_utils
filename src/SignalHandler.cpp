#include "tp_qt_utils/SignalHandler.h"

#include <QCoreApplication>
#include <QThread>

#include <csignal>

namespace tp_qt_utils
{

namespace
{
//##################################################################################################
void exitQt(int sig)
{
  TP_UNUSED(sig);
  if(QCoreApplication::instance() && QCoreApplication::instance()->thread() == QThread::currentThread())
    QCoreApplication::exit(0);
  else
    QThread::currentThread()->exit(0);
}
}

//##################################################################################################
void installSignalHandler()
{
  std::signal(SIGINT, exitQt);
  std::signal(SIGTERM, exitQt);
}

}
