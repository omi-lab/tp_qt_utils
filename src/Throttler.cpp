#include "tp_qt_utils/Throttler.h"

#include "tp_utils/TimeUtils.h"

#include <QTimer>

#include <limits>

namespace tp_qt_utils
{

//##################################################################################################
struct Throttler::SharedData
{
  QTimer timer;

  std::vector<Throttler*> throttlers;
  size_t runNext{0};
  int64_t yieldAfter{0};

  //################################################################################################
  SharedData()
  {
    QObject::connect(&timer, &QTimer::timeout, &timer, [&]
    {
      yieldAfter = tp_utils::currentTimeMicroseconds()+1000;
      do
      {
        if(runNext>=throttlers.size())
          runNext = 0;

        throttlers.at(runNext)->m_callback();
        runNext++;
      }while(!throttlers.empty() && !shouldYield());
    });
  }

  //################################################################################################
  bool shouldYield() const
  {
    return tp_utils::currentTimeMicroseconds()>yieldAfter;
  }
};

//##################################################################################################
Throttler::Throttler(const std::function<void()>& callback):
  m_callback(callback)
{

}

//##################################################################################################
Throttler::~Throttler()
{
  stop();
}

//##################################################################################################
void Throttler::start()
{
  auto& i = instance();
  if(std::find(i.throttlers.begin(), i.throttlers.end(), this) == i.throttlers.end())
  {
    i.throttlers.push_back(this);
    if(i.throttlers.size() == 1)
      i.timer.start(0);
  }
}

//##################################################################################################
void Throttler::stop()
{
  auto& i = instance();
  tpRemoveOne(i.throttlers, this);
  if(i.throttlers.empty())
    i.timer.stop();
}


//##################################################################################################
bool Throttler::shouldYield() const
{
  return instance().shouldYield();
}

//################################################################################################
Throttler::SharedData& Throttler::instance()
{
  thread_local static SharedData instance;
  return instance;
}

}
