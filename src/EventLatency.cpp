#include "tp_qt_utils/EventLatency.h"

#include "tp_utils/MutexUtils.h"
#include "tp_utils/TimeUtils.h"

#include <QCoreApplication>
#include <QEvent>

namespace tp_qt_utils
{

namespace
{
//##################################################################################################
struct CustomEvent_lt : public QEvent
{
  int64_t sentAt;

  //################################################################################################
  CustomEvent_lt():
    QEvent(QEvent::User),
    sentAt(tp_utils::currentTimeMS())
  {

  }
};
}

//##################################################################################################
struct EventLatency::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_utils::EventLatency::Private");
  TP_NONCOPYABLE(Private);

  std::string name;
  static TPMutex mutex;
  static std::unordered_map<std::string, int> results;

  //################################################################################################
  Private(const std::string& name_):
    name(name_)
  {

  }
};

TPMutex EventLatency::Private::mutex{TPM};
std::unordered_map<std::string, int> EventLatency::Private::results;

//##################################################################################################
EventLatency::EventLatency(const std::string& name):
  d(new Private(name))
{

}

//##################################################################################################
EventLatency::~EventLatency()
{
  delete d;
}

//##################################################################################################
std::unordered_map<std::string, int> EventLatency::results()
{
  TP_MUTEX_LOCKER(Private::mutex);
  return Private::results;
}

//##################################################################################################
std::string EventLatency::takeResults()
{
  std::string str;

  auto ret = results();

  size_t max{1};
  for(auto it = ret.begin(); it!=ret.end(); ++it)
    max = tpMax(it->first.size(), max);
  max++;

  for(auto it = ret.begin(); it!=ret.end(); ++it)
  {
    std::string name = it->first+": ";
    tp_utils::leftJustified(name, max);

    std::string count = std::to_string(it->second);
    tp_utils::rightJustified(count, 6);

    str += name + count + '\n';
  }

  return str;
}

//##################################################################################################
void EventLatency::timerEvent(QTimerEvent*)
{
  QCoreApplication::postEvent(this, new CustomEvent_lt());
}

//##################################################################################################
void EventLatency::customEvent(QEvent *event)
{
  auto e = dynamic_cast<CustomEvent_lt*>(event);
  if(!e)
    return;

  auto latency = tp_utils::currentTimeMS() - e->sentAt;
  {
    TP_MUTEX_LOCKER(Private::mutex);
    Private::results[d->name] = int(latency);
  }
}

}
